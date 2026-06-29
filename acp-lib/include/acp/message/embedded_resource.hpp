#include <optional>

#include <acp/message/annotations.hpp>
#include <acp/message/embedded_resource_resouce.hpp>
#include <acp/util/json_value.hpp>

namespace culpeo::acp::message
{
    struct EmbeddedResource
    {
        static constexpr std::string_view type{ "resource" };
        std::optional<Annotations> annotations;
        EmbeddedResourceResource resource;
        std::optional<util::JsonValue::Object> metadata;
    };
}