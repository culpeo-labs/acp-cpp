#pragma once

namespace culpeo::acp::message
{
    enum class ToolKind
    {
        Read,
        Edit,
        Delete,
        Move,
        Search,
        Execute,
        Think,
        Fetch,
        SwitchMode,
        Other
    };
}