/*
 * Copyright (c) 2017-2018, The Alloy Developers.
 * Portions Copyright (c) 2012-2017, The CryptoNote Developers, The Bytecoin Developers.
 *
 * This file is part of Alloy.
 *
 * This file is subject to the terms and conditions defined in the
 * file 'LICENSE', which is part of this source code package.
 */

#pragma once

#include <cstdint>
#include <string>

#include <boost/program_options.hpp>

namespace CryptoNote {

class MinerConfig {
public:
  MinerConfig();

  static void initOptions(boost::program_options::options_description& desc);
  void init(const boost::program_options::variables_map& options);

  std::string extraMessages;
  std::string startMining;
  uint32_t miningThreads;
};

} //namespace CryptoNote
