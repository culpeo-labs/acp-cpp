#pragma once

#include <optional>
#include <string>
#include <vector>

#include <acp/message/tool_call_content.hpp>
#include <acp/message/tool_call_id.hpp>
#include <acp/message/tool_call_location.hpp>
#include <acp/message/tool_call_status.hpp>
#include <acp/message/tool_kind.hpp>
#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct ToolCallUpdate
    {
        ToolCallId tool_call_id;
        std::optional<ToolKind> kind;
        std::optional<ToolCallStatus> status;
        std::optional<std::string> title;
        std::optional<std::vector<ToolCallContent>> content;
        std::optional<std::vector<ToolCallLocation>> locations;
        std::optional<util::JsonValue> raw_input;
        std::optional<util::JsonValue> raw_output;
        std::optional<util::JsonValue::Object> metadata;
    };
}