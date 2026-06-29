#pragma once

#include <expected>
#include <string>

namespace culpeo::acp::serialization
{
    template<typename T> inline constexpr bool always_false = false;

    enum class Error
    {
        invalid_value,
    };

    template<typename T>
    using Result = std::expected<T, Error>;


    template<typename T>
    struct Serializer
    {
        [[nodiscard]] static Result<std::string> serialize(const T& value) noexcept;

        [[nodiscard]] static Result<T> deserialize(std::string_view json) noexcept;
    };
}