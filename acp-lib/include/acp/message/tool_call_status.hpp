#pragma once

namespace culpeo::acp::message
{
    enum class ToolCallStatus
    {
        Pending,
        InProgress,
        Completed,
        Failed,
    };
}