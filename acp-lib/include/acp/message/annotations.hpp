#pragma once

#include "acp/util/json_value.hpp"
#include <optional>
#include <vector>

#include <acp/message/role.hpp>

namespace culpeo::acp::message
{
    struct Annotations
    {
        std::optional<std::vector<Role>> audience;
        std::optional<std::string> last_modified;
        std::optional<double> priority;
        std::optional<util::JsonValue::Object> metadata;
    };
}