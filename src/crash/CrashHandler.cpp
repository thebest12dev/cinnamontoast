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
#include "CrashHandler.h"
#include "TypeDefinitions.h"
#include <iostream>
#include <windows.h>
using namespace CinnamonToast;

// Internal functions
namespace {
void noCrashFunction() {};
LONG WINAPI signalHandler(EXCEPTION_POINTERS *ExceptionInfo) {
  if (ExceptionInfo->ExceptionRecord->ExceptionCode ==
      EXCEPTION_ACCESS_VIOLATION) {
    std::cout << "[FATAL] [signalHandler]: Program crashed! Segmentation fault!"
              << std::endl;
    std::cout << "[FATAL] [signalHandler]: Showing message! " << std::endl;
    MessageBox(NULL,
               "The program crashed due to a segmentation fault. Reinstalling "
               "the app may fix the issue.",
               "Program crashed!", MB_ICONERROR);
    exit(0x000003f7);
  }
  return EXCEPTION_CONTINUE_SEARCH; // Continue searching for another handler
                                    // (if any)
};
} // namespace

namespace CinnamonToast {
CrashHandler *CrashManager::handler = nullptr;
void CrashManager::setActiveCrashHandler(CrashHandler *handler_) {
  if (handler != nullptr) {
    handler->deactivate();
  }
  handler = handler_;
  handler_->activate();
};

CrashHandler *CrashManager::getActiveCrashHandler() { return handler; };
void CrashHandler::invokeCrash(std::string crashMessage) {
  if (throwCrash) {
    std::cout << "[FATAL] [invokeUnhandledExceptionCrash]: Program crashed! "
              << std::endl;
    std::cout << "[FATAL] [invokeUnhandledExceptionCrash]: Showing message! "
              << std::endl;
    MessageBox(NULL,
               "The program crashed due to an unspecified reason. Restarting "
               "the app may fix this issue.",
               "Program crashed!", MB_ICONERROR);
    exit(0x000003f8);
  }
}
bool Utilities::checkBit(unsigned int num, int n) {
  unsigned int mask = 1 << n; // Create a mask with 1 at the nth position
  return num & mask; // If the nth bit is 1, the result will be non-zero
}

CrashHandler::CrashHandler(CrashConfig cf)
    : customCrash(noCrashFunction), throwHandle(false), throwCrash(false),
      config(cf) {}
void CrashHandler::invokeUnhandledExceptionCrash(std::exception &ex) {
  if (throwHandle) {
    if (customCrash != noCrashFunction) {
      customCrash();
    }
    std::cout << "[FATAL] [invokeUnhandledExceptionCrash]: Program crashed! "
              << std::endl;
    std::cout << "[FATAL] [invokeUnhandledExceptionCrash]: Printing error and "
                 "showing message! "
              << std::endl;
    std::cout << "[FATAL] [<exception>]: " << ex.what() << std::endl;
    MessageBox(NULL,
               "The program crashed due to an unhandled exception. "
               "Reinstalling the app may fix this issue.",
               "Program crashed!", MB_ICONERROR);
    exit(0x000003f6);
  }
};
void CrashHandler::activate() {
  active = true;
  if (Utilities::checkBit(config.crashType, 0)) {
    SetUnhandledExceptionFilter(signalHandler);
  }
  if (Utilities::checkBit(config.crashType, 4)) {
    throwHandle = true;
  }
  if (Utilities::checkBit(config.crashType, 8)) {
    throwCrash = true;
  }
}
void CrashHandler::deactivate() {
  active = false;
  if (Utilities::checkBit(config.crashType, 0)) {
    SetUnhandledExceptionFilter(NULL);
  }
  if (Utilities::checkBit(config.crashType, 4)) {
    throwHandle = false;
  }
  if (Utilities::checkBit(config.crashType, 8)) {
    throwCrash = false;
  }
}
void CrashHandler::setUnhandledExceptionCrashFunction(CrashFunction function) {
  customCrash = function;
}
} // namespace CinnamonToast
