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

#include <string>

namespace System {

class Dispatcher;
class Ipv4Address;

class Ipv4Resolver {
public:
  Ipv4Resolver();
  explicit Ipv4Resolver(Dispatcher& dispatcher);
  Ipv4Resolver(const Ipv4Resolver&) = delete;
  Ipv4Resolver(Ipv4Resolver&& other);
  ~Ipv4Resolver();
  Ipv4Resolver& operator=(const Ipv4Resolver&) = delete;
  Ipv4Resolver& operator=(Ipv4Resolver&& other);
      Ipv4Address resolve(const std::string& host);

private:
  Dispatcher* dispatcher;
};

}
