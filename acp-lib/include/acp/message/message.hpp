#pragma once

#include <variant>

#include <acp/message/request_permission_request.hpp>
#include <acp/message/read_text_file_request.hpp>
#include <acp/message/write_text_file_request.hpp>
#include <acp/message/create_terminal_request.hpp>
#include <acp/message/terminal_output_request.hpp>
#include <acp/message/release_terminal_request.hpp>
#include <acp/message/wait_for_terminal_exit_request.hpp>
#include <acp/message/kill_terminal_request.hpp>

namespace culpeo::acp::messages
{
    using AgentRequest = std::variant<
        message::WriteTextFileRequest,
        message::ReadTextFileRequest,
        message::RequestPermissionRequest,
        message::CreateTerminalRequest,
        message::TerminalOutputRequest,
        message::ReleaseTerminalRequest,
        message::WaitForTerminalExitRequest,
        message::KillTerminalRequest
    >;

    using AgentResponse = std::variant<>;

    using Message = std::variant<
        AgentRequest,
        AgentResponse
    >;

}