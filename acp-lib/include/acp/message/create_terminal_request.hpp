#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include <acp/message/request_id.hpp>
#include <acp/message/env_variable.hpp>
#include <acp/message/session_id.hpp>
#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct CreateTerminalRequest
    {
        RequestId request_id;
        SessionId session_id;
        std::string command;
        std::optional<std::vector<std::string>> args;
        std::optional<std::vector<EnvVariable>> env;
        std::optional<std::string> cwd;
        std::optional<uint64_t> output_byte_limit;
        std::optional<util::JsonValue::Object> metadata;
    };
}