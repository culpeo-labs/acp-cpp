#pragma once

#include <optional>

#include <acp/message/permission_option_id.hpp>
#include <acp/message/permission_option_kind.hpp>
#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct PermissionOption
    {
        PermissionOptionId option_id;
        std::string name;
        PermissionOptionKind kind;
        std::optional<util::JsonValue::Object> metadata;
    };
}