#pragma once

#include <optional>

#include <acp/message/request_id.hpp>
#include <acp/message/session_id.hpp>
#include <acp/message/terminal_id.hpp>
#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct ReleaseTerminalRequest
    {
        RequestId request_id;
        SessionId session_id;
        TerminalId terminal_id;
        std::optional<util::JsonValue::Object> metadata;
    };
}