#include <optional>

#include <acp/message/annotations.hpp>

namespace culpeo::acp::message
{
    struct AudioContent
    {
        std::optional<Annotations> annotations;
        std::string data;
        std::string mime_type;
        std::optional<nlohmann::json> meta;
    };
}