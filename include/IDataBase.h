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

#include <string>
#include <system_error>

#include "IWriteBatch.h"
#include "IReadBatch.h"

namespace CryptoNote {

class IDataBase {
public:
  virtual ~IDataBase() {
  }

  virtual std::error_code write(IWriteBatch& batch) = 0;
  virtual std::error_code writeSync(IWriteBatch& batch) = 0;

  virtual std::error_code read(IReadBatch& batch) = 0;
};
}
