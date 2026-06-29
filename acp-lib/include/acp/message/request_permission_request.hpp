#pragma once

#include <optional>
#include <vector>

#include <acp/message/permission_option.hpp>
#include <acp/message/request_id.hpp>
#include <acp/message/tool_call_update.hpp>
#include <acp/util/json_value.hpp>
#include <acp/message/session_id.hpp>

namespace culpeo::acp::message
{
    struct RequestPermissionRequest
    {
        RequestId request_id;
        SessionId session_id;
        ToolCallUpdate tool_call;
        std::vector<PermissionOption> options;
        std::optional<util::JsonValue::Object> metadata;
    };
}