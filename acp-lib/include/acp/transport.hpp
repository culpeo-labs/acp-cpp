#include <expected>
#include <string>
#include <string_view>

namespace culpeo::acp::transport
{
    struct MessageSource
    {
        enum class ReadStatus
        {
            closed,
            error,
            fatal,
        };

        virtual ~MessageSource() = default;

        virtual std::expected<std::string, ReadStatus> read() noexcept = 0;
    };

    struct MessageSink
    {
        virtual ~MessageSink() = default;

        virtual void write(std::string_view frame) noexcept = 0;
    };
}