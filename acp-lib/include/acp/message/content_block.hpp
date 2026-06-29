#pragma once

#include <variant>

#include <acp/message/text_content.hpp>
#include <acp/message/image_content.hpp>
#include <acp/message/audio_content.hpp>
#include <acp/message/resource_link.hpp>
#include <acp/message/embedded_resource.hpp>

namespace culpeo::acp::message
{
    using ContentBlock = std::variant<TextContent, ImageContent, AudioContent, ResourceLink, EmbeddedResource>;
}