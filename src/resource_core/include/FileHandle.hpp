#pragma once
#include <cstdio>
#include <string>

namespace lab4::resource
{
class FileHandle
{
    std::FILE* handle_;

  public:
    FileHandle() = delete;

    explicit FileHandle(const std::string& path);

    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

    FileHandle(FileHandle&& donor) noexcept;
    FileHandle& operator=(FileHandle&& donor) noexcept;

    ~FileHandle();

    [[nodiscard]] bool isOpen() const noexcept;
};
} // namespace lab4::resource