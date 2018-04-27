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

#include <chrono>

namespace System {

class Dispatcher;

class Timer {
public:
  Timer();
  explicit Timer(Dispatcher& dispatcher);
  Timer(const Timer&) = delete;
  Timer(Timer&& other);
  ~Timer();
  Timer& operator=(const Timer&) = delete;
  Timer& operator=(Timer&& other);
  void sleep(std::chrono::nanoseconds duration);

private:
  Dispatcher* dispatcher;
  void* context;
  int timer;
};

}
