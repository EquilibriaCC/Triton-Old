/*
 * Copyright (c) 2017-2018, The Alloy Developers.
 * Portions Copyright (c) 2012-2017, The CryptoNote Developers, The Bytecoin Developers.
 *
 * This file is part of Alloy.
 *
 * This file is subject to the terms and conditions defined in the
 * file 'LICENSE', which is part of this source code package.
 */

#include "ContextGroup.h"
#include <cassert>

namespace System {

ContextGroup::ContextGroup(Dispatcher& dispatcher) : dispatcher(&dispatcher) {
  contextGroup.firstContext = nullptr;
}

ContextGroup::ContextGroup(ContextGroup&& other) : dispatcher(other.dispatcher) {
  if (dispatcher != nullptr) {
    assert(other.contextGroup.firstContext == nullptr);
    contextGroup.firstContext = nullptr;
    other.dispatcher = nullptr;
  }
}

ContextGroup::~ContextGroup() {
  if (dispatcher != nullptr) {
    interrupt();
    wait();
  }
}

ContextGroup& ContextGroup::operator=(ContextGroup&& other) {
  assert(dispatcher == nullptr || contextGroup.firstContext == nullptr);
  dispatcher = other.dispatcher;
  if (dispatcher != nullptr) {
    assert(other.contextGroup.firstContext == nullptr);
    contextGroup.firstContext = nullptr;
    other.dispatcher = nullptr;
  }

  return *this;
}

void ContextGroup::interrupt() {
  assert(dispatcher != nullptr);
  for (NativeContext* context = contextGroup.firstContext; context != nullptr; context = context->groupNext) {
    dispatcher->interrupt(context);
  }
}

void ContextGroup::spawn(std::function<void()>&& procedure) {
  assert(dispatcher != nullptr);
  NativeContext& context = dispatcher->getReusableContext();
  if (contextGroup.firstContext != nullptr) {
    context.groupPrev = contextGroup.lastContext;
    assert(contextGroup.lastContext->groupNext == nullptr);
    contextGroup.lastContext->groupNext = &context;
  } else {
    context.groupPrev = nullptr;
    contextGroup.firstContext = &context;
    contextGroup.firstWaiter = nullptr;
  }

  context.interrupted = false;
  context.group = &contextGroup;
  context.groupNext = nullptr;
  context.procedure = std::move(procedure);
  contextGroup.lastContext = &context;
  dispatcher->pushContext(&context);
}

void ContextGroup::wait() {
  if (contextGroup.firstContext != nullptr) {
    NativeContext* context = dispatcher->getCurrentContext();
    context->next = nullptr;

    assert(!context->inExecutionQueue);
    context->inExecutionQueue = true;

    if (contextGroup.firstWaiter != nullptr) {
      assert(contextGroup.lastWaiter->next == nullptr);
      contextGroup.lastWaiter->next = context;
    } else {
      contextGroup.firstWaiter = context;
    }

    contextGroup.lastWaiter = context;
    dispatcher->dispatch();
    assert(context == dispatcher->getCurrentContext());
  }
}

}
