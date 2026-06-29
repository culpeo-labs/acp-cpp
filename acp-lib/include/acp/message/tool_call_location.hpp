#pragma once

#include <cstdint>
#include <optional>

#include "acp/util/json_value.hpp"

namespace culpeo::acp::message
{
    struct ToolCallLocation
    {
        std::string path;
        std::optional<uint32_t> line;
        std::optional<util::JsonValue::Object> metadata;
    };
}