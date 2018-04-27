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

#include <istream>
#include "IInputStream.h"

namespace Common {

class StdInputStream : public IInputStream {
public:
  StdInputStream(std::istream& in);
  StdInputStream& operator=(const StdInputStream&) = delete;
  size_t readSome(void* data, size_t size) override;

private:
  std::istream& in;
};

}
