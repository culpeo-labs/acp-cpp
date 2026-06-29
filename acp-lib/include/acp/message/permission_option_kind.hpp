#pragma once

namespace culpeo::acp::message
{
    enum class PermissionOptionKind
    {
        AllowOnce,
        AllowAlways,
        RejectOnce,
        RejectAlways,
    };
}