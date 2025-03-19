/**
* Copyright (c) 2025 thebest12lines
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge, publish, distribute,
* sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
* BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
* DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
typedef unsigned char byte;
#include "Definitions.h"
#if !defined(CTOAST_API) && !defined(CTOAST_BUILDING)
    #define CTOAST_API __declspec(dllimport);
#endif
#define ctoast CinnamonToast::
namespace CinnamonToast { };

#ifdef CTOAST_SHARED_LIBRARY
    #ifdef _WIN32
        #define CTOAST_API __declspec(dllexport)
    #elif __linux__
        #define CTOAST_API __attribute__((visibility("default")))
    #endif
#endif

using namespace std;
using namespace CinnamonToast;