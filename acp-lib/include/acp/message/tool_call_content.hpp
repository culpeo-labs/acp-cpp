#pragma once

#include <variant>

#include <acp/message/content.hpp>
#include <acp/message/diff.hpp>
#include <acp/message/terminal.hpp>

namespace culpeo::acp::message
{
    using ToolCallContent = std::variant<Content, Diff, Terminal>;
}