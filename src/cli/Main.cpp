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

#ifndef CTOAST_TESTS
// set byte to unsigned char to prevent ambiguity
using byte = unsigned char;

// if windows
#ifdef _WIN32
#include <windows.h>
// visual styles
// #pragma comment(
// version = '6.0.0.0' processorArchitecture = '*' publicKeyToken =
//'6595b64144ccf1df' language = '*'\"")
#endif
#include "../core/logging/LogBuffer.h"
#include "../core/memory/HeapPool.h"
#include "Main.h"
#include "Utilities.h"
#ifdef CTOAST_NO_CONSOLE
// use windows APIs intead of int main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  // expression to load ctoast
  cinnamontoast::LogBuffer logbuf;
  std::cout.rdbuf(&logbuf);
  return cinnamontoast::cliMain(__argc,
                                cinnamontoast::utilities::cstrArrToVector(
                                    const_cast<const char **> __argv));
}
#else
// main function
#include "../core/logging/LogInstance.h"
#include "../core/logging/LogUtil.h"

#include "Console.h"
int main(int argc, char const *argv[]) {
  // expression to load ctoast

  cinnamontoast::utilities::initLogs();
  return cinnamontoast::cliMain(
      argc, cinnamontoast::utilities::cstrArrToVector(argv));
}
#endif

#endif
