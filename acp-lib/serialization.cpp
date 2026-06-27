#include <expected>
#include <string_view>

#include "./serialization.hpp"

using namespace culpeo::acp;

template<template<typename> typename Container, typename T> serialization::Result<std::string> serialization::serialize(const Container<T>& value) noexcept
{
    nlohmann::json j{};
    for (const auto& item : value)
    {
        if (auto serialized = serialization::serialize(item); serialized)
        {
            j.push_back(serialized.value());
        }
        else
        {
            return serialized.error();
        }
    }
    return j.dump();
}

template<template<typename> typename Container, typename T> serialization::Result<Container<T>> serialization::deserialize(const nlohmann::json& json) noexcept
{
    if (json.is_array())
    {
        Container<T> result{};
        for (const auto& item : json)
        {
            if (auto deserialized = serialization::deserialize<T>(item); deserialized)
            {
                result.push_back(deserialized.value());
            }
            else
            {
                return deserialized.error();
            }
        }
        return result;
    }
    return std::unexpected{ serialization::Error::invalid_value };
}

// template<> std::expected<std::string, serialization::Error> serialization::serialize<message::Role>(const message::Role& role) noexcept
// {
//     switch (role)
//     {
//         case message::Role::assistant:
//             return "assistant";
//         case message::Role::user:
//             return "user";
//     }
//     return std::unexpected{ serialization::Error::invalid_value };
// }

// template<> std::expected<message::Role, serialization::Error> serialization::deserialize<message::Role>(std::string_view json) noexcept
// {
//     if (json == "assistant")
//     {
//         return message::Role::assistant;
//     }
//     if (json == "user")
//     {
//         return message::Role::user;
//     }
//     return std::unexpected{ serialization::Error::invalid_value };
// }

// template<> std::expected<std::string, serialization::Error> serialization::serialize<message::Annotations>(const message::Annotations& annotations) noexcept
// {
//     nlohmann::json j{};
//     if (annotations.audience)
//     {

//         j["audience"] = annotations.audience.
//     }
//     // Implementation for serializing Annotations
//     return {};
// }

// template<> std::expected<message::Annotations, serialization::Error> serialization::deserialize<message::Annotations>(std::string_view json) noexcept
// {
//     // Implementation for deserializing Annotations
//     return {};
// }