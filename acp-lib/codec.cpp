#include <exception>

#include <acp/codec.hpp>

using namespace culpeo::acp;

std::expected<std::string, codec::Error> codec::encode(const messages::Message& message) noexcept
{
    std::terminate();
    // Implementation for encoding a message
}

std::expected<messages::Message, codec::Error> codec::decode(std::string_view frame) noexcept
{
    std::terminate();
    // Implementation for decoding a frame
}