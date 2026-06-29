#pragma once

#include <cstdint>
#include <optional>
#include <string>

#include <acp/message/request_id.hpp>
#include <acp/message/session_id.hpp>
#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct ReadTextFileRequest
    {
        RequestId request_id;
        SessionId session_id;
        std::string file_path;
        std::optional<uint32_t> line;
        std::optional<uint32_t> limit;
        std::optional<util::JsonValue::Object> metadata;
    };
}