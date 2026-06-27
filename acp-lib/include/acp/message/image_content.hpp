#include <optional>

#include <acp/message/annotations.hpp>

namespace culpeo::acp::message
{
    struct ImageContent
    {
        std::optional<Annotations> annotations;
        std::string data;
        std::string mime_type;
        std::optional<std::string> uri;
        std::optional<nlohmann::json> meta;
    };
}