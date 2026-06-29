
#pragma once

#include <acp/util/checked_string.hpp>

namespace culpeo::acp::message
{
    namespace detail
    {
        struct ToolCallIdPolicy
        {
            static constexpr bool validate(std::string_view value) noexcept
            {
                return true;
            }
        };
    }

    using ToolCallId = culpeo::acp::util::CheckedString<detail::ToolCallIdPolicy>;
}