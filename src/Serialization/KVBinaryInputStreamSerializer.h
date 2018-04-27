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

#include <Common/IInputStream.h>
#include "ISerializer.h"
#include "JsonInputValueSerializer.h"

namespace CryptoNote {

class KVBinaryInputStreamSerializer : public JsonInputValueSerializer {
public:
  KVBinaryInputStreamSerializer(Common::IInputStream& strm);

  virtual bool binary(void* value, size_t size, Common::StringView name) override;
  virtual bool binary(std::string& value, Common::StringView name) override;
};

}
