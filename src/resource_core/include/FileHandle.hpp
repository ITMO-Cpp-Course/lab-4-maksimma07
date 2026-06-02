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

    explicit FileHandle(const std::string& path); // explicit запрещает неявное копирование std_string в FileHandle

    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;

    FileHandle(FileHandle&& donor) noexcept;
    FileHandle& operator=(FileHandle&& donor) noexcept; // noexcept обещает компилятору, что метод не выбросит исключения

    ~FileHandle();

    [[nodiscard]] bool isOpen() const noexcept; // const не меняет состояние объекта
};
} // namespace lab4::resource