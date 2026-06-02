#include "FileHandle.hpp"
#include "ResourceError.hpp"
#include "ResourceManager.hpp"

#include <catch2/catch_all.hpp>
#include <memory>
#include <string>
#include <utility>

using namespace lab4::resource;

TEST_CASE("Управление временем жизни FileHandle", "[resource]")
{
    SECTION("Захват ресурса при создании и освобождение при разрушении")
    {
        const std::string name = "acquire_release.txt";

        {
            const FileHandle fh(name);
            REQUIRE(fh.isOpen());
        }
        SUCCEED("Файл закрыт после выхода из области видимости");
    }

    SECTION("Корректная передача владения через перемещение")
    {
        FileHandle source("move_src.txt");
        REQUIRE(source.isOpen());

        FileHandle destination(std::move(source));

        REQUIRE_FALSE(source.isOpen());
        REQUIRE(destination.isOpen());
    }

    SECTION("Конструктор с пустым именем файла выбрасывает ResourceError")
    {
        REQUIRE_THROWS_AS(FileHandle(""), ResourceError);
    }
}

TEST_CASE("Кеширование в ResourceManager", "[manager]")
{
    ResourceManager manager;
    const std::string shared = "cached_file.txt";

    SECTION("Повторный запрос возвращает тот же самый объект")
    {
        const auto first = manager.obtain(shared);
        const auto second = manager.obtain(shared);

        REQUIRE(first.get() == second.get());
        REQUIRE(first.use_count() == 2);
    }

    SECTION("После удаления всех внешних ссылок создаётся новый объект")
    {
        const void* old_addr = nullptr;

        {
            const auto temp = manager.obtain(shared);
            old_addr = temp.get();
        }

        const auto renewed = manager.obtain(shared);

        REQUIRE(renewed.get() != old_addr);
        REQUIRE(renewed.use_count() == 1);
    }

    SECTION("Разные имена файлов создают независимые объекты")
    {
        const auto alpha = manager.obtain("alpha.txt");
        const auto beta = manager.obtain("beta.txt");

        REQUIRE(alpha.get() != beta.get());
    }
}