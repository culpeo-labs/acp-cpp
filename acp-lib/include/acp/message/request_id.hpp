#pragma once

#include <string>
#include <variant>

namespace culpeo::acp::message
{
    using RequestId = std::variant<std::string, int64_t, std::nullptr_t>;
}