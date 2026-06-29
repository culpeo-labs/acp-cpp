#pragma once

#include <string_view>

#include <acp/util/checked_string.hpp>

namespace culpeo::acp::message
{
    namespace detail
    {
        struct TerminalIdPolicy
        {
            static constexpr bool validate(std::string_view value) noexcept
            {
                return true;
            }

        };
    }

    using TerminalId = culpeo::acp::util::CheckedString<detail::TerminalIdPolicy>;
}