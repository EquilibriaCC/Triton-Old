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

namespace Common { namespace Console {

enum class Color : uint8_t {
  Default,

  Blue,
  Green,
  Red,
  Yellow,
  White,
  Cyan,
  Magenta,

  BrightBlue,
  BrightGreen,
  BrightRed,
  BrightYellow,
  BrightWhite,
  BrightCyan,
  BrightMagenta
};

void setTextColor(Color color);
bool isConsoleTty();

}}
