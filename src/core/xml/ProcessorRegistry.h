#pragma once

#include "../ui/Component.h"
#include "../ui/Window.h"
#include "TypeDefinitions.h"
#include <functional>
#include <tinyxml2.h>
#include <unordered_map>
namespace reflect {
using Processor = std::function<std::pair<Component &, std::string>(
    Window *win, tinyxml2::XMLElement *element)>;
class ProcessorRegistry {
private:
  static std::unordered_map<std::string, Processor> mapOfProcessors;

public:
  static void createProcessor(Processor processor,
                              const std::string &elementId);
  static std::pair<Component &, std::string>
  invokeProcessor(const std::string &elementId, Window *win,
                  tinyxml2::XMLElement *element);
};
} // namespace reflect