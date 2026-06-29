#pragma once

#include <optional>
#include <string>
#include <string_view>

#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct Diff
    {
        static constexpr std::string_view type{ "diff" };
        std::string path;
        std::optional<std::string> old_text;
        std::string new_text;
        std::optional<util::JsonValue::Object> metadata;
    };
}