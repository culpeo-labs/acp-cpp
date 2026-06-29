#include <acp/util//checked_string.hpp>

namespace culpeo::acp::util
{
    namespace detail
    {
        struct UuidPolicy
        {
            static constexpr bool validate(std::string_view value) noexcept
            {
                return value.size() == 36 && value[8] == '-' && value[13] == '-' && value[18] == '-' && value[23] == '-';
            }
        };
    }

    using Uuid = CheckedString<detail::UuidPolicy>;
}