#include <concepts>
#include <expected>
#include <string_view>

#include <glaze/core/seek.hpp>
#include <glaze/util/key_transformers.hpp>
#include <glaze/glaze.hpp>

#include <acp/message/annotations.hpp>
#include <acp/message/audio_content.hpp>
#include <acp/message/blob_resource_contents.hpp>
#include <acp/message/create_terminal_request.hpp>
#include <acp/message/content.hpp>
#include <acp/message/content_block.hpp>
#include <acp/message/diff.hpp>
#include <acp/message/env_variable.hpp>
#include <acp/message/image_content.hpp>
#include <acp/message/kill_terminal_request.hpp>
#include <acp/message/read_text_file_request.hpp>
#include <acp/message/permission_option.hpp>
#include <acp/message/permission_option_kind.hpp>
#include <acp/message/request_permission_request.hpp>
#include <acp/message/release_terminal_request.hpp>
#include <acp/message/terminal.hpp>
#include <acp/message/terminal_output_request.hpp>
#include <acp/message/text_content.hpp>
#include <acp/message/text_resource_contents.hpp>
#include <acp/message/tool_call_content.hpp>
#include <acp/message/tool_call_location.hpp>
#include <acp/message/tool_call_status.hpp>
#include <acp/message/tool_call_update.hpp>
#include <acp/message/tool_kind.hpp>
#include <acp/message/wait_for_terminal_exit_request.hpp>
#include <acp/message/write_text_file_request.hpp>
#include <acp/message/role.hpp>
#include <acp/serialization.hpp>
#include <acp/util/checked_string.hpp>
#include <acp/util/json_value.hpp>
#include <acp/util/uuid.hpp>

using namespace culpeo::acp;

template<typename T>
    requires std::default_initializable<T>
struct serialization::Serializer<T>
{
    [[nodiscard]] static serialization::Result<std::string> serialize(const T& value) noexcept
    {
        if (auto result = glz::write_json(value); result)
        {
            return result.value();
        }
        return std::unexpected{ serialization::Error::invalid_value };
    }

    [[nodiscard]] static serialization::Result<T> deserialize(std::string_view json) noexcept
    {
        T value{};
        if (auto err = glz::read_json(value, json); !err)
        {
            return value;
        }
        return std::unexpected{ serialization::Error::invalid_value };
    }
};

template<typename P>
struct serialization::Serializer<util::CheckedString<P>>
{
    [[nodiscard]] static serialization::Result<std::string> serialize(const util::CheckedString<P>& value) noexcept
    {
        if (auto result = glz::write_json(value); result)
        {
            return result.value();
        }
        return std::unexpected{ serialization::Error::invalid_value };
    }

    [[nodiscard]] static serialization::Result<util::CheckedString<P>> deserialize(std::string_view json) noexcept
    {

        std::string str{};
        if (auto err = glz::read_json(str, json); !err)
        {
            util::CheckedString<P> val{ std::move(str) };
            if  (val.valid())
            {
                return val;
            }
        }
        return std::unexpected{ serialization::Error::invalid_value };
    }
};

template struct serialization::Serializer<util::JsonValue>;
template struct serialization::Serializer<util::Uuid>;
template struct serialization::Serializer<message::WaitForTerminalExitRequest>;
template struct serialization::Serializer<message::WriteTextFileRequest>;
template struct serialization::Serializer<message::ReadTextFileRequest>;
template struct serialization::Serializer<message::RequestPermissionRequest>;
template struct serialization::Serializer<message::CreateTerminalRequest>;
template struct serialization::Serializer<message::TerminalOutputRequest>;
template struct serialization::Serializer<message::ReleaseTerminalRequest>;
template struct serialization::Serializer<message::KillTerminalRequest>;

namespace glz
{
    template<>
    struct from<JSON, util::JsonValue>
    {
        template<auto Opts>
        static void op(util::JsonValue& value, is_context auto && ctx, auto && it, auto && end)
        {
            util::JsonValue::Container container{};
            parse<JSON>::op<Opts>(container, ctx, it, end);

            value = std::visit([](auto&& arg) -> util::JsonValue { return util::JsonValue{std::forward<decltype(arg)>(arg)}; }, container);
        }
    };

    template<>
    struct to<JSON, util::JsonValue>
    {
        template<auto Opts>
        static void op(const util::JsonValue& value, is_context auto && ctx, auto && b, auto && ix) noexcept
        {
            if (value.is_null())
            {
                serialize<JSON>::op<Opts>(nullptr, ctx, b, ix);
                return;
            }
            else if (value.is_bool())
            {
                serialize<JSON>::op<Opts>(value.as_bool(), ctx, b, ix);
                return;
            }
            else if (value.is_int())
            {
                serialize<JSON>::op<Opts>(value.as_int(), ctx, b, ix);
                return;
            }
            else if (value.is_double())
            {
                serialize<JSON>::op<Opts>(value.as_double(), ctx, b, ix);
                return;
            }
            else if (value.is_string())
            {
                serialize<JSON>::op<Opts>(value.as_string(), ctx, b, ix);
                return;
            }
            else if (value.is_array())
            {
                serialize<JSON>::op<Opts>(value.as_array(), ctx, b, ix);
                return;
            }
            else if (value.is_object())
            {
                serialize<JSON>::op<Opts>(value.as_object(), ctx, b, ix);
                return;
            }
        }
    };

    template<typename P>
    struct from<JSON, util::CheckedString<P>>
    {
        template<auto Opts>
        static void op(util::CheckedString<P>& value, is_context auto && ctx, auto && it, auto && end)
        {
            std::string str{};
            parse<JSON>::op<Opts>(str, ctx, it, end);
            value = util::CheckedString<P>{std::move(str)};
        }
    };

    template<typename P>
    struct to<JSON, util::CheckedString<P>>
    {
        template<auto Opts>
        static void op(const util::CheckedString<P>& value, is_context auto && ctx, auto && b, auto && ix) noexcept
        {
            serialize<JSON>::op<Opts>(value.view(), ctx, b, ix);
        }
    };

    template<typename T>
        requires std::same_as<T, message::WriteTextFileRequest>
              || std::same_as<T, message::ReadTextFileRequest>
              || std::same_as<T, message::Annotations>
              || std::same_as<T, message::TextContent>
              || std::same_as<T, message::ImageContent>
              || std::same_as<T, message::AudioContent>
              || std::same_as<T, message::ResourceLink>
              || std::same_as<T, message::TextResourceContents>
              || std::same_as<T, message::BlobResourceContents>
              || std::same_as<T, message::EmbeddedResource>
              || std::same_as<T, message::Content>
              || std::same_as<T, message::Diff>
              || std::same_as<T, message::Terminal>
              || std::same_as<T, message::ToolCallLocation>
              || std::same_as<T, message::ToolCallUpdate>
              || std::same_as<T, message::PermissionOption>
              || std::same_as<T, message::RequestPermissionRequest>
              || std::same_as<T, message::EnvVariable>
              || std::same_as<T, message::CreateTerminalRequest>
              || std::same_as<T, message::TerminalOutputRequest>
              || std::same_as<T, message::ReleaseTerminalRequest>
              || std::same_as<T, message::WaitForTerminalExitRequest>
              || std::same_as<T, message::KillTerminalRequest>
    struct meta<T>
    {
        static constexpr std::string rename_key(const std::string_view key) {
            if (key == "metadata") return "_meta";
            return to_camel_case(key);
        }
    };

    template<typename T>
        requires std::same_as<T, message::ToolKind>
                || std::same_as<T, message::ToolCallStatus>
                || std::same_as<T, message::Role>
                || std::same_as<T, message::PermissionOptionKind>
    struct meta<T>: snake_case {};

    template<>
    struct meta<message::ContentBlock>
    {
        static constexpr std::string_view tag = "type";
        static constexpr auto ids = std::array{
             message::TextContent::type,
             message::ImageContent::type,
             message::AudioContent::type,
             message::ResourceLink::type,
             message::EmbeddedResource::type
        };
    };

    template<>
    struct meta<message::ToolCallContent>
    {
        static constexpr std::string_view tag = "type";
        static constexpr auto ids = std::array{
             message::Content::type,
             message::Diff::type,
             message::Terminal::type
        };
    };
}

