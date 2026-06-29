#pragma once

#include <optional>
#include <string>

#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct TextResourceContents
    {
        std::optional<std::string> mime_type;
        std::string text;
        std::string uri;
        std::optional<util::JsonValue::Object> metadata;
    };
}