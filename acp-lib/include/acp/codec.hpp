#include <expected>
#include <string>
#include <string_view>

#include <acp/message/message.hpp>

namespace culpeo::acp::codec
{
    enum class Error
    {
        invalid_frame,
    };

    std::expected<std::string, Error> encode(const messages::Message& message) noexcept;
    std::expected<messages::Message, Error> decode(std::string_view frame) noexcept;
}