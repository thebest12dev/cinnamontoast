/**
 * Copyright (c) 2025 thebest12lines
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED
 * "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#pragma once
#include "TypeDefinitions.h"
#include <cstdint>
#include <exception>
#include <string>
#include <windows.h>

#define CRASH_UNHANDLED_EXCEPTION 0x10
#define CRASH_INVOKE 0x100
#define CRASH_SEGFAULT 0x1
typedef void (*CrashFunction)();

namespace CinnamonToast {
struct CrashConfig {
  uint32_t messageType;
  uint32_t crashType;
};
class CrashHandler {
private:
  CrashFunction customCrash;
  bool active;
  bool throwHandle;
  bool throwCrash;
  CrashConfig config;
  __declspec(dllimport) void activate();
  __declspec(dllimport) void deactivate();

public:
  __declspec(dllimport) CrashHandler(CrashConfig cf);
  __declspec(dllimport) void setCustomCrashHandler(CrashFunction func);
  __declspec(dllimport) void invokeCrash(std::string crashMessage);

  // Note: explicitly need to define try-catch block and to call this method
  __declspec(dllimport) void invokeUnhandledExceptionCrash(std::exception &ex);
  __declspec(dllimport) void
  setUnhandledExceptionCrashFunction(CrashFunction function);

  friend class CrashManager;
};
class CrashManager {
private:
  static CrashHandler *handler;

public:
  __declspec(dllimport) static void
  setActiveCrashHandler(CrashHandler *handler_);
  __declspec(dllimport) static CrashHandler *getActiveCrashHandler();
};
namespace Utilities {
bool checkBit(unsigned int num, int n);
}
} // namespace CinnamonToast