#pragma once

#include <optional>
#include <string>

#include <acp/message/request_id.hpp>
#include <acp/message/session_id.hpp>
#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct WriteTextFileRequest
    {
        RequestId request_id;
        SessionId session_id;
        std::string path;
        std::string content;
        std::optional<util::JsonValue::Object> metadata;
    };
}