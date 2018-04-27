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

#include <cstdint>
#include <string>

namespace Tools
{
  namespace Base58
  {
    std::string encode(const std::string& data);
    bool decode(const std::string& enc, std::string& data);

    std::string encode_addr(uint64_t tag, const std::string& data);
    bool decode_addr(std::string addr, uint64_t& tag, std::string& data);
  }
}
