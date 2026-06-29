#pragma once

#include <concepts>
#include <map>
#include <string>
#include <variant>
#include <vector>
#include <string_view>

namespace culpeo::acp::util
{
    class JsonValue
    {
    public:
        using Array = std::vector<JsonValue>;
        using Object = std::map<std::string, JsonValue, std::less<>>;
        using Container = std::variant<std::nullptr_t, bool, int64_t, double, std::string, Array, Object>;

        JsonValue() noexcept : m_value{ nullptr } {}
        JsonValue(std::nullptr_t) noexcept : m_value{ nullptr } {}

        JsonValue(bool value) noexcept : m_value{ value } {}

        template<typename T>
            requires std::integral<T> && (!std::same_as<T, bool>)
        JsonValue(T value) noexcept : m_value{static_cast<int64_t>(value)} {}

        template<typename T>
            requires std::floating_point<T>
        JsonValue(T value) noexcept : m_value{static_cast<double>(value)} {}

        JsonValue(const char* value) : m_value{ std::string(value) } {}
        JsonValue(const std::string& value) : m_value{ value } {}
        JsonValue(std::string&& value) : m_value{ std::move(value) } {}
        JsonValue(const Array& value) : m_value{ value } {}
        JsonValue(Array&& value) : m_value{ std::move(value) } {}
        JsonValue(const Object& value) : m_value{ value } {}
        JsonValue(Object&& value) : m_value{ std::move(value) } {}

        JsonValue& operator=(std::nullptr_t) noexcept { m_value = nullptr; return *this; }
        JsonValue& operator=(bool value) noexcept { m_value = value; return *this; }

        template<typename T>
            requires std::integral<T> && (!std::same_as<T, bool>)
        JsonValue& operator=(T value) noexcept { m_value = static_cast<int64_t>(value); return *this; }

        template<typename T>
            requires std::floating_point<T>
        JsonValue& operator=(T value) noexcept { m_value = static_cast<double>(value); return *this; }

        inline JsonValue& operator=(const char* value) { m_value = std::string(value); return *this; }
        inline JsonValue& operator=(const std::string& value) { m_value = value; return *this; }
        inline JsonValue& operator=(std::string&& value) { m_value = std::move(value); return *this; }
        inline JsonValue& operator=(const Array& value) { m_value = value; return *this; }
        inline JsonValue& operator=(Array&& value) { m_value = std::move(value); return *this; }
        inline JsonValue& operator=(const Object& value) { m_value = value; return *this; }
        inline JsonValue& operator=(Object&& value) { m_value = std::move(value); return *this; }

        inline bool is_null() const noexcept { return std::holds_alternative<std::nullptr_t>(m_value); }
        inline bool is_bool() const noexcept { return std::holds_alternative<bool>(m_value); }
        inline bool is_int() const noexcept { return std::holds_alternative<int64_t>(m_value); }
        inline bool is_double() const noexcept { return std::holds_alternative<double>(m_value); }
        inline bool is_string() const noexcept { return std::holds_alternative<std::string >(m_value); }
        inline bool is_array() const noexcept { return std::holds_alternative<Array>(m_value); }
        inline bool is_object() const noexcept { return std::holds_alternative<Object>(m_value); }

        bool as_bool() const noexcept;
        int64_t as_int() const noexcept;
        double as_double() const noexcept;

        const std::string& as_string() const & noexcept;
        std::string& as_string() & noexcept;
        std::string&& as_string() && noexcept;

        const Array& as_array() const & noexcept;
        Array& as_array() & noexcept;
        Array&& as_array() && noexcept;

        const Object& as_object() const & noexcept;
        Object& as_object() & noexcept;
        Object&& as_object() && noexcept;

        const JsonValue& operator[](std::string_view key) const & noexcept;
        JsonValue& operator[](std::string_view key) & noexcept;
        JsonValue&& operator[](std::string_view key) && noexcept;

        const JsonValue& operator[](size_t index) const & noexcept;
        JsonValue& operator[](size_t index) & noexcept;
        JsonValue&& operator[](size_t index) && noexcept;
    private:
        Container m_value;
    };
}