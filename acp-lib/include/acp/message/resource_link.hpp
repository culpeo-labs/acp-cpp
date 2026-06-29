#pragma once

#include <optional>
#include <string>

#include <acp/message/annotations.hpp>
#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct ResourceLink
    {
        static constexpr std::string_view type{ "resource_link" };
        std::optional<Annotations> annotations;
        std::optional<std::string> description;
        std::optional<std::string> mime_type;
        std::string name;
        std::optional<int64_t> size;
        std::optional<std::string> title;
        std::string uri;
        std::optional<util::JsonValue::Object> metadata;
    };
}