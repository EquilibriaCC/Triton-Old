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

#include <CryptoNoteCore/BlockchainStorage.h>
#include "CryptoNoteCore/SwappedVector.h"

namespace CryptoNote {

class SwappedBlockchainStorage : public BlockchainStorage::IBlockchainStorageInternal {
public:
  SwappedBlockchainStorage(const std::string& indexFileName, const std::string& dataFileName);
  virtual ~SwappedBlockchainStorage() override;

  virtual void pushBlock(RawBlock&& rawBlock) override;

  //Returns MemoryBlockchainStorage with elements from [splitIndex, blocks.size() - 1].
  //Original SwappedBlockchainStorage will contain elements from [0, splitIndex - 1].
  virtual std::unique_ptr<BlockchainStorage::IBlockchainStorageInternal> splitStorage(uint32_t splitIndex) override;

  virtual RawBlock getBlockByIndex(uint32_t index) const override;
  virtual uint32_t getBlockCount() const override;

private:
  mutable SwappedVector<RawBlock> blocks;
};

}
