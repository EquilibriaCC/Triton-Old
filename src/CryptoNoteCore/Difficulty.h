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
#include <vector>

#include "crypto/hash.h"

namespace CryptoNote {

typedef std::uint64_t Difficulty;
bool check_hash(const Crypto::Hash &hash, Difficulty difficulty);

}
