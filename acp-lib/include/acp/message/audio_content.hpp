#pragma once

#include <optional>

#include <acp/message/annotations.hpp>
#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct AudioContent
    {
        static constexpr std::string_view type{ "audio" };
        std::optional<Annotations> annotations;
        std::string data;
        std::string mime_type;
        std::optional<util::JsonValue::Object> metadata;
    };
}