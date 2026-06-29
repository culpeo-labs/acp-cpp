#pragma once

#include <optional>

#include <acp/message/content_block.hpp>
#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct Content
    {
        static constexpr std::string_view type{ "content" };
        ContentBlock content;
        std::optional<util::JsonValue::Object> metadata;
    };
}