#include "FileHandle.hpp"
#include "ResourceError.hpp"
#include <utility>

namespace lab4::resource
{
FileHandle::FileHandle(const std::string& path)
{
    handle_ = std::fopen(path.c_str(), "a+");
    if (handle_ == nullptr)
    {
        throw ResourceError("Cannot acquire file: " + path);
    }
}

FileHandle::~FileHandle()
{
    if (handle_ != nullptr)
    {
        std::fclose(handle_);
        handle_ = nullptr;
    }
}

FileHandle::FileHandle(FileHandle&& donor) noexcept : handle_(donor.handle_)
{
    donor.handle_ = nullptr;
}

FileHandle& FileHandle::operator=(FileHandle&& donor) noexcept
{
    if (this == &donor)
    {
        return *this;
    }

    if (handle_ != nullptr)
    {
        std::fclose(handle_);
    }

    handle_ = donor.handle_;
    donor.handle_ = nullptr;

    return *this;
}

bool FileHandle::isOpen() const noexcept
{
    return handle_ != nullptr;
}
} // namespace lab4::resource