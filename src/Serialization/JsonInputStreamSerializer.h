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

#include <iosfwd>
#include <string>
#include <vector>
#include "../Common/JsonValue.h"
#include "JsonInputValueSerializer.h"

namespace CryptoNote {

//deserialization
class JsonInputStreamSerializer : public JsonInputValueSerializer {
public:
  JsonInputStreamSerializer(std::istream& stream);
  virtual ~JsonInputStreamSerializer();
};

}
