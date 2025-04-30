#include "Object.h"

namespace CinnamonToast {
unsigned int Object::getUID() const noexcept { return 0; }
std::string Object::toString() noexcept { return typeid(*this).name(); }
Object::~Object() = default;

} // namespace CinnamonToast