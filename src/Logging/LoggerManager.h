/*
 * Copyright (c) 2017-2018, The Triton Developers.
 * Portions Copyright (c) 2012-2017, The CryptoNote Developers, The Bytecoin Developers.
 *
 * This file is part of Triton.
 *
 * This file is subject to the terms and conditions defined in the
 * file 'LICENSE', which is part of this source code package.
 */

#pragma once

#include <list>
#include <memory>
#include <mutex>
#include "../Common/JsonValue.h"
#include "LoggerGroup.h"

namespace Logging {

class LoggerManager : public LoggerGroup {
public:
  LoggerManager();
  void configure(const Common::JsonValue& val);
  virtual void operator()(const std::string& category, Level level, boost::posix_time::ptime time, const std::string& body) override;

private:
  std::vector<std::unique_ptr<CommonLogger>> loggers;
  std::mutex reconfigureLock;
};

}
