#pragma once

#include <string_view>

#include <acp/util/checked_string.hpp>

namespace culpeo::acp::message
{
    namespace detail
    {
        struct PermissionOptionIdPolicy
        {
            static constexpr bool validate(std::string_view value) noexcept
            {
                return true;
            }

        };
    }

    using PermissionOptionId = culpeo::acp::util::CheckedString<detail::PermissionOptionIdPolicy>;
}