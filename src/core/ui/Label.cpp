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
#include "Label.h"
#include "../Utilities.h"
#include "Console.h"
#include "Definitions.h"
#include "TypeDefinitions.h"
#include "Window.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif
using namespace reflect::console;
using namespace reflect::utilities;
void reflect::Label::setFont(std::string font) {
  fontStr = font;
  if (font == "default") {
    fontStr = DEFAULT_FONT;
  }
}
void reflect::Label::setFontSize(int size) { fontSize = size; }
std::string reflect::Label::getText() { return text; }

void reflect::Label::render(WindowHandle &parentHWND,
                            WindowHandle &windowHWND) {
#ifdef _WIN32
  if (!IsWindow(parentHWND)) {
    reflectError("parent WindowHandle is invalid!");
    std::exit(REFLECT_ERROR_WIN_PARENT_HWND_INVALID);
  }
  reflect::Window *window = reinterpret_cast<reflect::Window *>(
      GetWindowLongPtr(windowHWND, GWLP_USERDATA));

  // Create the label window
  hwnd = CreateWindow("STATIC",              // Predefined class for a label
                      text.c_str(),          // Label text
                      WS_VISIBLE | WS_CHILD, // Styles: visible and child window
                      position.x,
                      position.y + window->getProperty<int>(
                                       "customTitleBarSize"), // Position (x, y)
                      size.x, size.y, // Size (width, height)
                      parentHWND,     // Parent window handle
                      NULL,           // No menu or child ID
                      winstance,      // Instance handle
                      NULL            // Additional application data
  );

  if (!hwnd) {
    std::cout << getLastErrorAsString();
    return;
  }

  // Create a custom font
  HFONT hFont = reflect::utilities::getFont(fontStr, fontSize);

  if (hFont) {
    // Set the font for the label
    SendMessage(hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
  }

  // Resize the label based on the text and font size
  HDC hdc = GetDC(hwnd);
  if (hdc) {
    // Select the font into the device context
    HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

    // Calculate the size of the text
    SIZE textSize;
    GetTextExtentPoint32(hdc, text.c_str(), (int)text.length(), &textSize);

    // Update the label's size
    SetWindowPos(hwnd,                         // Handle to the label
                 NULL,                         // No z-order change
                 position.x, position.y,       // X and Y (ignored here)
                 textSize.cx + (fontSize * 2), // New width (padding added)
                 textSize.cy,                  // New height
                 SWP_NOZORDER | SWP_NOMOVE // Don't change z-order or position
    );

    // Restore the old font and release the device context
    SelectObject(hdc, oldFont);
    ReleaseDC(hwnd, hdc);
  }
#elif __linux__
  // do nothing, as you cannot create a label in linux
#endif
}

void reflect::Label::setVisible(bool flag) {
#ifdef _WIN32
  ShowWindow(this->hwnd, flag ? SW_SHOW : SW_HIDE);
#elif __linux__

#endif
}
reflect::Label::Label(std::string text, Vector2 pos)
    : position(pos), size(Vector2(0, 0)), text(text) {
  initializeObject(REFLECT_OBJECT_LABEL, REFLECT_OBJECT_TEXTCOMPONENT);
}