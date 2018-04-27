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

#include <memory>

namespace CryptoNote {

class IBlockchainCache;
class Currency;

class IBlockchainCacheFactory {
public:
  virtual ~IBlockchainCacheFactory() {}

  virtual std::unique_ptr<IBlockchainCache> createRootBlockchainCache(const Currency& currency) = 0;
  virtual std::unique_ptr<IBlockchainCache> createBlockchainCache(const Currency& currency, IBlockchainCache* parent, uint32_t startIndex = 0) = 0;
};

} //namespace CryptoNote
