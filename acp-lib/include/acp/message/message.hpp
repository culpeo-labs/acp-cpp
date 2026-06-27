#include <optional>
#include <string>
#include <variant>
#include <stdint.h>

#include <nlohmann/json.hpp>
#include <vector>

namespace culpeo::acp::messages {

    using Message = std::string;


    // using RequestId = std::variant<std::string, uint64_t, std::nullptr_t>;
    // using SessionId = std::string;
    // using ToolCallId = std::string;
    // enum class ToolKind
    // {
    //     read,
    //     edit,
    //     delete_,
    //     move,
    //     search,
    //     execute,
    //     think,
    //     fetch,
    //     switch_mode,
    //     other,
    // };

    // enum class ToolCallStatus
    // {
    //     pending,
    //     in_progress,
    //     completed,
    //     failed,
    // };

    // struct WriteTextFileRequest
    // {
    //     SessionId session_id;
    //     std::string path;
    //     std::string content;
    //     std::optional<nlohmann::json> metadata;
    // };

    // struct ReadTextFileRequest
    // {
    //     SessionId session_id;

    // }

    // struct ToolCallUpdate
    // {
    //     ToolCallId tool_call_id;
    //     std::optional<ToolKind> kind;
    //     std::optional<ToolCallStatus> status;
    //     std::optional<std::string> title;

    // }

    // struct Content
    // {
    //     ContentBlock content;
    //     std::optional<nlohmann::json> metadata;
    // };






}