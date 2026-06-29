#pragma once

#include <variant>

#include <acp/message/blob_resource_contents.hpp>
#include <acp/message/text_resource_contents.hpp>

namespace culpeo::acp::message
{
    using EmbeddedResourceResource = std::variant<TextResourceContents, BlobResourceContents>;
}