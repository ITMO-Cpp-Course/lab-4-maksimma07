#include "ResourceManager.hpp"
#include <utility>

namespace lab4::resource
{
std::shared_ptr<FileHandle> ResourceManager::obtain(const std::string& filename)
{
    auto found = registry_.find(filename); // итератор unodered_map

    if (found != registry_.end())
    {
        auto locked = found->second.lock(); // превращаем weak в shared
        if (locked != nullptr)
        {
            return locked;
        }
    }

    auto fresh = std::make_shared<FileHandle>(filename);
    registry_[filename] = fresh;
    return fresh;
}
} // namespace lab4::resource