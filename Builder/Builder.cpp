#include "json_builder.h"

#include <iostream>
#include <string_view>

using namespace std::literals;

// =============================================================================
// Прототипы тестов
// =============================================================================

void TestStringJSON();
void TestArrayJSON();
void TestDictJSON();
void TestGeneralJSON();

void PrintTestDescription(std::string_view msg, std::ostream& os = std::cout);

// =============================================================================
// Главная функция
// =============================================================================

int main() {
    try {
        TestStringJSON();
        TestArrayJSON();
        TestDictJSON();
        TestGeneralJSON();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
        return 1;
    }
    catch (...) {
        std::cerr << "Неизвестная ошибка\n";
        return 1;
    }

    return 0;
}

// =============================================================================
// Вспомогательные функции
// =============================================================================

// Функция выводит сообщение, обрамлённое линиями из символов =,
// длина которых подстраивается под текст (минимум 30).
void PrintTestDescription(std::string_view msg, std::ostream& os) {
    size_t width = std::max(static_cast<size_t>(30), msg.length() + 2);
    std::string border(width, '=');
    os << "\n" << border << '\n'
       << msg << '\n'
       << border << "\n";
}

// =============================================================================
// Тесты
// =============================================================================

void TestStringJSON() {
    PrintTestDescription("String JSON");
    json::Print(
        json::Document{
            json::Builder{}
                .Value("just a string"s)
                .Build()
        },
        std::cout
    );
}

void TestArrayJSON() {
    PrintTestDescription("Array JSON");
    json::Print(
        json::Document{
            json::Builder{}
                .StartArray()
                    .Value(1)
                    .Value(2)
                    .Value(3)
                .EndArray()
                .Build()
        },
        std::cout
    );
}

void TestDictJSON() {
    PrintTestDescription("Dict JSON");
    json::Print(
        json::Document{
            json::Builder{}
                .StartDict()
                    .Key("1"s).StartDict().EndDict()
                    .Key("2"s).Value(2)
                .EndDict()
                .Build()
        },
        std::cout
    );
}

void TestGeneralJSON() {
    PrintTestDescription("General JSON");
    json::Print(
        json::Document{
            json::Builder{}
                .StartDict()
                    .Key("key1"s).Value(123)
                    .Key("key2"s).Value("value2"s)
                    .Key("key3"s).StartArray()
                        .Value(456)
                        .StartDict().EndDict()
                        .StartDict()
                            .Key(""s).Value(nullptr)
                        .EndDict()
                        .Value(""s)
                    .EndArray()
                .EndDict()
                .Build()
        },
        std::cout
    );
}
