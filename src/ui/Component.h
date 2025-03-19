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
#ifdef _WIN32
    #pragma once
    #include <cstdint>
    #include <windows.h>
    #include "Vector2.h"
    #include "Colors.h"
    #include "../TypeDefinitions.h"
    namespace CinnamonToast {
        class Component {
            protected:
                HINSTANCE winstance;
                HWND hwnd;
                
                HINSTANCE parentInstance;
                // Window parentWindow;

                Vector2 position;
                Vector2 size;
                
            
            public:
                shared Component(/* args */);
                shared virtual void Render(HWND& parentHWND, HWND& windowHWND) = 0;
                shared void SetVisible(bool flag);
                shared void Add(Component& comp);
                shared void SetSize(Vector2 size);
                shared void SetVisible(int cmd);
                shared void SetColor(uint8_t r, uint8_t g, uint8_t b);
                shared void SetColor(Color3 color);

                shared void SetColor(Color3Array color);
                shared ~Component();
                friend class Window;
                friend class Label;
                friend class Button;
        };
    } 
#elif __linux__
    #pragma once
    #include <cstdint>
    // #include "Window.h"
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <string>
    #include "Vector2.h"
    #include <vector>
    #include "../TypeDefinitions.h"
    namespace CinnamonToast {
        class Component {
            protected:
                Vector2 position;
                Vector2 size;
                bool visible;
                
                int color[3];
                vector<Component*> children;
            public:
                Component(/* args */);
                shared void SetVisible(bool flag);
                shared void Add(Component* comp);
                shared void SetSize(Vector2 size);
                shared Vector2 GetSize();
                shared Vector2 GetPosition();
                shared bool GetVisible();
                shared int* GetColor();
                virtual shared string GetProperty(string name) {return "null";};
                shared void SetVisible(int cmd);
                shared void SetColor(uint8_t r, uint8_t g, uint8_t b);
                virtual ~Component() {};
                friend class Window;
                friend class Label;
                friend class Button;
        };
    } 

#endif