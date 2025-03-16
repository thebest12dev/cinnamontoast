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

// define byte as unsigned char to prevent conflicts
typedef unsigned char byte; 

// if win32
#ifdef _WIN32
    // include windows.h
    #include <windows.h>
#endif

// standard libraries we need
#include <string>
#include <vector>
#include <cstdint>
#include <iostream>
#include <exception>
#include <filesystem>


// other libraries
#include "../lib/tinyxml2.h"

// our header files here
#include "Main.h"
#include "Console.h"
#include "CToastAPI.h"
#include "Utilities.h"
#include "Definitions.h"
#include "CrashHandler.h"
#include "TypeDefinitions.h"
// ui components
#include "ui/Label.h"
#include "ui/Button.h"
#include "ui/Colors.h"
#include "ui/Vector2.h"
#include "ui/Component.h"
#include "ui/Components.h"
#include "ui/TextComponent.h"

// windows-specific code
#ifdef _WIN32

    // include commctrl.h (for visual styles)
    #include <commctrl.h>
    
    // standard libs
    #include <cstdint>
    #include <filesystem>
    #include <iostream>
    #include <string>
    #include <vector>
    


    //using namespaces and alias
    using namespace CinnamonToast::Console;
    using namespace CinnamonToast::Utilities;

    namespace fs = std::filesystem;


    /**
    * Invokes and loads a .xml file and also loads the specific libraries. It will setup the GUI as well as
    * registering APIs for the libraries to use.
    */
    int ctoast InvokeExecutable(string xmlFile) {
        // load the xml file
        tinyxml2::XMLDocument doc;
       
        // platform
        info("platform: "+GetOSPlatformAndVersion(), "CLIMain");

        // common control stuff
        INITCOMMONCONTROLSEX icex;
        icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        icex.dwICC = ICC_STANDARD_CLASSES;
        InitCommonControlsEx(&icex);

        // file doesnt exist
        if (!fs::exists(xmlFile)) {
            // error and return
            error("file not found!");
            return error_file_not_found;
        }

        // debug print and load xml file
        debug("loading XML file...","InvokeExecutable");
        tinyxml2::XMLError eResult = doc.LoadFile(xmlFile.c_str());
        
        // error handling
        if (eResult != tinyxml2::XML_SUCCESS) {
            error(string("cannot load XML file: "+string(doc.ErrorStr())));
            return error_generic_xml_error;
        }

        // get the root element
        debug("getting root...","InvokeExecutable");
        tinyxml2::XMLElement* root = doc.FirstChildElement("root");
        // handling
        if (root == nullptr) {
            error("no root element found.");
            return error_xml_no_root;
        }
        
        // checking compat
        debug("file is compatible with app?","InvokeExecutable");
        const uint32_t version = stoi(root->Attribute("version"));
        if (version > app_internal_version) {
            // handle and return
            error("file not compatible! please upgrade to a newer version.");
            return error_xml_not_compatible;
        }
        tinyxml2::XMLElement* winXml = root->FirstChildElement("window");
        if (winXml == nullptr) {
            error("no window element found.");
            return error_xml_no_window;
        }
        
        #ifdef _WIN32
            debug("getting HINSTANCE...","InvokeExecutable");
            HINSTANCE hInstance = GetModuleHandle(nullptr);
            debug("creating window...","InvokeExecutable");
            Window win(hInstance);
        #endif
        
        debug("window title: "+string(winXml->Attribute("title")),"InvokeExecutable");
        win.SetTitle(winXml->Attribute("title"));
        debug("resizing window...","InvokeExecutable");
        win.SetSize(Vector2(stoi(winXml->Attribute("width")), stoi(winXml->Attribute("height"))));
        string bgColor = winXml->Attribute("bgColor");
        debug("setting window background color...","InvokeExecutable");
        if (bgColor == "systemDefault") {
            win.SetColor(255,255,255);
        } else {
            if (bgColor.at(0) == '#' && bgColor.length() == 7) {
                
                const string hex = bgColor.substr(1);

                const uint8_t r = stoi(hex.substr(0,2), nullptr, 16);
                const uint8_t g = stoi(hex.substr(2,2), nullptr, 16);
                const uint8_t b = stoi(hex.substr(4,2), nullptr, 16);
                const Color3 color = { r,g,b };
                win.SetColor(color);
            } else {
                error("invalid hex color representation");
                return error_hex_color_malformed;
            }
            
            
        }
        debug("parsing labels...","InvokeExecutable");
        for (tinyxml2::XMLElement* label = winXml->FirstChildElement("label"); label != nullptr; label = label->NextSiblingElement("label")) {
            // Access attributes
            string contents = label->GetText();
            string id = label->Attribute("id");
            Vector2 position(stoi(label->Attribute("x")),stoi(label->Attribute("y")));
            Label labelComp(contents, position);
            labelComp.SetFont(label->Attribute("font"));
            labelComp.SetFontSize(stoi(label->Attribute("fontSize")));
            win.Add(labelComp, id);
            
        }
        debug("parsing buttons...", "InvokeExecutable");
        for (tinyxml2::XMLElement* button = winXml->FirstChildElement("button"); button != nullptr; button = button->NextSiblingElement("button")) {
            string contents = button->GetText();
            string id = button->Attribute("id");
            Vector2 position(stoi(button->Attribute("x")), stoi(button->Attribute("y")));
            Button buttonComp(contents, position);
            buttonComp.SetFont(button->Attribute("font"));
            buttonComp.SetFontSize(stoi(button->Attribute("fontSize")));
            win.Add(buttonComp,id);
            

        }
        debug("loading libraries...", "InvokeExecutable");
        for (tinyxml2::XMLElement* sharedLib = winXml->FirstChildElement("library"); sharedLib != nullptr; sharedLib = sharedLib->NextSiblingElement("library")) {
            HMODULE hDll = LoadLibrary((const char*) fs::absolute(fs::path(xmlFile)).parent_path().c_str());
            if (!hDll) {
                error("cannot load shared library", "InvokeExecutable");
                return error_cannot_load_shared_library;
            }
            debug("loaded shared library!", "InvokeExecutable");

            // Get the address of the Add function
            SharedLibraryMain mainFunc = (SharedLibraryMain)GetProcAddress(hDll, "CToastMain");
            if (!mainFunc) {
                error("cannot find CToastMain function of library!", "InvokeExecutable");

                FreeLibrary(hDll); // Free the DLL
                return error_cannot_load_library_function;
            }
            CToastAPI ctoastApi = { ExternalAPI::GetComponentById, ExternalAPI::GetComponentText };
            mainFunc(&ctoastApi);
        }
        debug("entering main loop...","InvokeExecutable");
        win.SetVisible(true);
       
        return win.Run();
    }
    int ctoast CLIMain(const uint8_t argc, const vector<string> argv) {
        CrashConfig config = {};
        config.CrashType = crash_invoke | crash_segfault | crash_unhandled_exception;

        CrashHandler* ch = new CrashHandler(config);
        CrashManager::SetActiveCrashHandler(ch);

        try {
            println(app_name+string(" ")+app_version);
            if (argv.size() == 1) {
                error("error: no files specified. please pass an argument to a valid file");
                error("error code: ERROR_NO_FILES_SPECIFIED");
                return error_no_files_specified;
            } else {
                info("launching executable...","CLIMain");
                return CinnamonToast::InvokeExecutable(argv[1]);
            }
        } catch (exception e) {
            ch->InvokeUnhandledExceptionCrash(e);
        }
    }   
    

    
#elif __linux__
    #include <cstdint>
    #include <filesystem>
    #include <iostream>
    #include <string>
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    
    #include <vector>



    using namespace CinnamonToast::Console;
    using namespace CinnamonToast::Utilities;
    namespace fs = std::filesystem;



    int ctoast InvokeExecutable(string xmlFile) {
        tinyxml2::XMLDocument doc;
        // Load the XML file
        info("Platform: "+GetOSPlatformAndVersion(), "CLIMain");
        if (!fs::exists(xmlFile)) {
                error("file not found!");
            return error_file_not_found;
        }
        debug("loading XML file...","InvokeExecutable");
        tinyxml2::XMLError eResult = doc.LoadFile(xmlFile.c_str());
        
        if (eResult != tinyxml2::XML_SUCCESS) {
            error(string("cannot load XML file: "+string(doc.ErrorStr())));
            return error_generic_xml_error;
        }

        // Get the root element
        debug("getting root...","InvokeExecutable");
        tinyxml2::XMLElement* root = doc.FirstChildElement("root");
        if (root == nullptr) {
            error("no root element found.");
            return error_xml_no_root;
        }
        debug("file is compatible with app?","InvokeExecutable");
        const uint32_t version = stoi(root->Attribute("version"));
        if (version > app_internal_version) {
            error("file not compatible! please upgrade to a newer version.");
        }
        tinyxml2::XMLElement* winXml = root->FirstChildElement("window");
        if (winXml == nullptr) {
            error("no window element found.");
            return error_xml_no_window;
        }
        
        #ifdef _WIN32
            debug("getting HINSTANCE...","InvokeExecutable");
            HINSTANCE hInstance = GetModuleHandle(nullptr);
            debug("creating window...","InvokeExecutable");
            Window win(hInstance);
        #elif __linux__
            Window win(XOpenDisplay(NULL));
        #endif
        
        debug("window title: "+string(winXml->Attribute("title")),"InvokeExecutable");
        win.SetTitle(winXml->Attribute("title"));
        debug("resizing window...","InvokeExecutable");
        win.SetSize(Vector2(stoi(winXml->Attribute("width")), stoi(winXml->Attribute("height"))));
        string bgColor = winXml->Attribute("bgColor");
        debug("setting window background color...","InvokeExecutable");
        if (bgColor == "systemDefault") {
            win.SetColor(255,255,255);
        } else {
            if (bgColor.at(0) == '#' && bgColor.length() == 7) {
                
                const string hex = bgColor.substr(1);

                const uint8_t r = stoi(hex.substr(0,2), nullptr, 16);
                const uint8_t g = stoi(hex.substr(2,2), nullptr, 16);
                const uint8_t b = stoi(hex.substr(4,2), nullptr, 16);
                
                win.SetColor(r,g,b);
            } else {
                error("invalid hex color representation");
                return error_hex_color_malformed;
            }
            
            
        }
        debug("parsing labels...","InvokeExecutable");
        for (tinyxml2::XMLElement* label = winXml->FirstChildElement("label"); label != nullptr; label = label->NextSiblingElement("label")) {
            // Access attributes
            string contents = label->GetText();
            Vector2 position(stoi(label->Attribute("x")),stoi(label->Attribute("y")));
            Label* labelComp = new Label(contents, position);
            labelComp->SetFont(label->Attribute("font"));
            labelComp->SetFontSize(stoi(label->Attribute("fontSize")));
            
            win.Add(labelComp);
            
            
        }
        debug("entering main loop...","InvokeExecutable");
        win.SetVisible(true);
        
        return win.Run();
    }
    int ctoast CLIMain(const uint8_t argc, const vector<string> argv) {
        println(app_name+string(" ")+app_version);
        if (argv.size() == 1) {
            error("error: no files specified. please pass an argument to a valid file");
            error("error code: ERROR_NO_FILES_SPECIFIED");
            return error_no_files_specified;
        } else {
            info("launching executable...","CLIMain");
            return CinnamonToast::InvokeExecutable(argv[1]);
        }
    }   
#endif
// Main entrypoint

#ifndef shared_library
int main(const int argc, const char* argv[]) {
    return CinnamonToast::CLIMain(argc, CstrArrToVector(argv));
}
#endif