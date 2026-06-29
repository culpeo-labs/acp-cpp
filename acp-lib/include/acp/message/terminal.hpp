#pragma once

#include <optional>
#include <string_view>

#include <acp/message/terminal_id.hpp>
#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct Terminal
    {
        static constexpr std::string_view type{ "terminal" };
        TerminalId terminal_id;
        std::optional<util::JsonValue::Object> metadata;
    };
}