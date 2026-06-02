#pragma once
#include "FileHandle.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace lab4::resource
{
class ResourceManager
{
    std::unordered_map<std::string, std::weak_ptr<FileHandle>> registry_;

  public:
    ResourceManager() = default;

    std::shared_ptr<FileHandle> obtain(const std::string& filename);
};
} // namespace lab4::resource