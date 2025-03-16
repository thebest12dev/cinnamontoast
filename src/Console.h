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
#pragma once

#include "TypeDefinitions.h"
#include <iostream>
#include <string>
using namespace std;

namespace CinnamonToast {
    namespace Console {
        
        // std:: part is omitted because of `using namespace std;`.
        template <typename T>
        shared void print(const T& obj) {
            cout << obj;
        };      
        template <typename T>
        shared void println(const T& obj) {
            cout << obj << endl;
        };
        template <typename T>
        shared void error(const T& obj, string ctx = "default") {
            cerr << "[ERROR] " << "[" << ctx << "]: " << obj << endl;
        };
        template <typename T>
        shared void info(const T& obj, string ctx = "default") {
            cout << "[INFO] " << "[" << ctx << "]: " << obj << endl;
        };
        template <typename T>
        shared void warn(const T& obj, string ctx = "default") {
            cout << "[WARN] " << "[" << ctx << "]: " << obj << endl;
        };
        template <typename T>
        shared void debug(const T& obj, string ctx = "default") {
            cout << "[DEBUG] " << "[" << ctx << "]: " << obj << endl;
        };
    }
}

