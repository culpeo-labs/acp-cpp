#include <optional>

#include <acp/message/annotations.hpp>

namespace culpeo::acp::message
{
    struct TextContent
    {
        std::optional<Annotations> annotations;
        std::string text;
        std::optional<nlohmann::json> meta;
    };
}