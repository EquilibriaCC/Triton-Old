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

#include <vector>
#include <string>
#include <utility>

namespace CryptoNote {

class IWriteBatch {
public:
  virtual std::vector<std::pair<std::string, std::string>> extractRawDataToInsert() = 0;
  virtual std::vector<std::string> extractRawKeysToRemove() = 0;
};

} //namespace CryptoNote
