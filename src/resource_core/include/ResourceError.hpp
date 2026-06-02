#pragma once
#include <stdexcept>
#include <string>

namespace lab4::resource
{
class ResourceError : public std::runtime_error
{
  public:
    explicit ResourceError(const std::string& what) : std::runtime_error(what) {}
};
} // namespace lab4::resource