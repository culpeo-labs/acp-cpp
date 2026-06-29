#pragma once

#include <optional>
#include <string>

#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct EnvVariable
    {
        std::string name;
        std::string value;
        std::optional<util::JsonValue::Object> metadata;
    };
}
