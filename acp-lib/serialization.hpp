#pragma once

#include <expected>
#include <string>

#include <nlohmann/json.hpp>

#include <acp/message/role.hpp>
#include <acp/message/annotations.hpp>

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
    Result<nlohmann::json> serialize(const T& value) noexcept
    {
        static_assert(always_false<T>, "Type T must be a valid type for serialization");
        return {};
    }

    template<typename T>
    Result<T> deserialize(const nlohmann::json& json) noexcept
    {
        static_assert(always_false<T>, "Type T must be a valid type for deserialization");
        return {};
    }


    template<template<typename> typename Container, typename T> Result<nlohmann::json> serialize(const Container<T>& value) noexcept;
    template<template<typename> typename Container, typename T> Result<Container<T>> deserialize(const nlohmann::json& json) noexcept;
    // template<> Result<nlohmann::json> serialize<acp::message::Role>(const acp::message::Role& role) noexcept;
    // template<> Result<acp::message::Role> deserialize<acp::message::Role>(const nlohmann::json& json) noexcept;
    // template<> Result<nlohmann::json> serialize<acp::message::Annotations>(const acp::message::Annotations& annotations) noexcept;
    // template<> Result<acp::message::Annotations> deserialize<acp::message::Annotations>(const nlohmann::json& json) noexcept;

}