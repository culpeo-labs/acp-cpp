#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <acp/util/json_value.hpp>
#include <acp/util/uuid.hpp>
#include <acp/message/write_text_file_request.hpp>
#include <acp/serialization.hpp>

using namespace culpeo::acp;

using JsonValue            = util::JsonValue;
using Uuid                 = util::Uuid;
using WriteTextFileRequest = message::WriteTextFileRequest;
using SessionId            = message::SessionId;

namespace
{
    constexpr std::string_view valid_uuid   = "550e8400-e29b-41d4-a716-446655440000";
    constexpr std::string_view invalid_uuid = "not-a-valid-uuid";
}

TEST_CASE("JsonValue serialization", "[serialization]")
{
    SECTION("null serializes to null")
    {
        JsonValue v;
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == "null");
    }

    SECTION("true serializes to true")
    {
        JsonValue v(true);
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == "true");
    }

    SECTION("false serializes to false")
    {
        JsonValue v(false);
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == "false");
    }

    SECTION("integer serializes to number")
    {
        JsonValue v(42);
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == "42");
    }

    SECTION("negative integer serializes to number")
    {
        JsonValue v(-7);
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == "-7");
    }

    SECTION("double serializes to number")
    {
        JsonValue v(1.5);
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == "1.5");
    }

    SECTION("string serializes to quoted string")
    {
        JsonValue v("hello");
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == R"("hello")");
    }

    SECTION("array serializes to JSON array")
    {
        JsonValue v(JsonValue::Array{JsonValue(1), JsonValue(2), JsonValue(3)});
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == "[1,2,3]");
    }

    SECTION("empty array serializes to []")
    {
        JsonValue v(JsonValue::Array{});
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == "[]");
    }

    SECTION("object serializes to JSON object")
    {
        JsonValue v(JsonValue::Object{{"key", JsonValue("value")}});
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == R"({"key":"value"})");
    }

    SECTION("empty object serializes to {}")
    {
        JsonValue v(JsonValue::Object{});
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == "{}");
    }

    SECTION("nested object serializes correctly")
    {
        JsonValue v(JsonValue::Object{
            {"items", JsonValue(JsonValue::Array{JsonValue(1), JsonValue(true), JsonValue("x")})}
        });
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == R"({"items":[1,true,"x"]})");
    }
}

TEST_CASE("JsonValue deserialization", "[serialization]")
{
    SECTION("null deserializes from null")
    {
        auto result = serialization::Serializer<JsonValue>::deserialize("null");
        REQUIRE(result);
        auto value = result.value();
        REQUIRE(value.is_null());
    }

    SECTION("true deserializes from true")
    {
        auto result = serialization::Serializer<JsonValue>::deserialize("true");
        REQUIRE(result);
        auto value = result.value();
        REQUIRE(value.is_bool());
        REQUIRE(value.as_bool() == true);
    }

    SECTION("false deserializes from false")
    {
        auto result = serialization::Serializer<JsonValue>::deserialize("false");
        REQUIRE(result);
        auto value = result.value();
        REQUIRE(value.is_bool());
        REQUIRE(value.as_bool() == false);
    }

    SECTION("integer deserializes from number")
    {
        auto result = serialization::Serializer<JsonValue>::deserialize("42");
        REQUIRE(result);
        auto value = result.value();
        REQUIRE(value.is_int());
        REQUIRE(value.as_int() == 42);
    }

    SECTION("double deserializes from fractional number")
    {
        auto result = serialization::Serializer<JsonValue>::deserialize("3.14");
        REQUIRE(result);
        auto value = result.value();
        REQUIRE(value.is_double());
        REQUIRE_THAT(value.as_double(), Catch::Matchers::WithinRel(3.14, 1e-9));
    }

    SECTION("string deserializes from quoted string")
    {
        auto result = serialization::Serializer<JsonValue>::deserialize(R"("hello")");
        REQUIRE(result);
        auto value = result.value();
        REQUIRE(value.is_string());
        REQUIRE(value.as_string() == "hello");
    }

    SECTION("array deserializes from JSON array")
    {
        auto result = serialization::Serializer<JsonValue>::deserialize("[1,2,3]");
        REQUIRE(result);
        auto value = result.value();
        REQUIRE(value.is_array());
        REQUIRE(value.as_array().size() == 3);
        REQUIRE(value[size_t{0}].as_int() == 1);
        REQUIRE(value[size_t{1}].as_int() == 2);
        REQUIRE(value[size_t{2}].as_int() == 3);
    }

    SECTION("empty array deserializes from []")
    {
        auto result = serialization::Serializer<JsonValue>::deserialize("[]");
        REQUIRE(result);
        auto value = result.value();
        REQUIRE(value.is_array());
        REQUIRE(value.as_array().empty());
    }

    SECTION("object deserializes from JSON object")
    {
        auto result = serialization::Serializer<JsonValue>::deserialize(R"({"key":"value"})");
        REQUIRE(result);
        auto value = result.value();
        REQUIRE(value.is_object());
        REQUIRE(value["key"].is_string());
        REQUIRE(value["key"].as_string() == "value");
    }

    SECTION("empty object deserializes from {}")
    {
        auto result = serialization::Serializer<JsonValue>::deserialize("{}");
        REQUIRE(result);
        auto value = result.value();
        REQUIRE(value.is_object());
        REQUIRE(value.as_object().empty());
    }

    SECTION("nested structure deserializes correctly")
    {
        auto result = serialization::Serializer<JsonValue>::deserialize(R"({"name":"alice","scores":[10,20],"active":true})");
        REQUIRE(result);
        auto value = result.value();
        REQUIRE(value.is_object());
        REQUIRE(value["name"].as_string() == "alice");
        REQUIRE(value["scores"].is_array());
        REQUIRE(value["scores"][size_t{0}].as_int() == 10);
        REQUIRE(value["scores"][size_t{1}].as_int() == 20);
        REQUIRE(value["active"].as_bool() == true);
    }

    SECTION("mixed-type array deserializes correctly")
    {
        auto result = serialization::Serializer<JsonValue>::deserialize(R"([null,true,1,"x"])");
        REQUIRE(result);
        auto value = result.value();
        REQUIRE(value.is_array());
        REQUIRE(value[size_t{0}].is_null());
        REQUIRE(value[size_t{1}].is_bool());
        REQUIRE(value[size_t{2}].is_int());
        REQUIRE(value[size_t{3}].is_string());
    }
}

TEST_CASE("JsonValue roundtrip", "[serialization]")
{
    SECTION("null roundtrips")
    {
        auto serialization_result = serialization::Serializer<JsonValue>::serialize(JsonValue{});
        REQUIRE(serialization_result);
        auto deserialization_result = serialization::Serializer<JsonValue>::deserialize(serialization_result.value());
        REQUIRE(deserialization_result);
        REQUIRE(deserialization_result.value().is_null());
    }

    SECTION("bool roundtrips")
    {
        auto b = GENERATE(true, false);
        JsonValue original(b);
        auto serialization_result = serialization::Serializer<JsonValue>::serialize(original);
        REQUIRE(serialization_result);
        auto deserialization_result = serialization::Serializer<JsonValue>::deserialize(serialization_result.value());
        REQUIRE(deserialization_result);
        REQUIRE(deserialization_result.value().is_bool());
        REQUIRE(deserialization_result.value().as_bool() == b);
    }

    SECTION("integer roundtrips")
    {
        JsonValue original(int64_t{9000000000LL});
        auto serialization_result = serialization::Serializer<JsonValue>::serialize(original);
        REQUIRE(serialization_result);
        auto deserialization_result = serialization::Serializer<JsonValue>::deserialize(serialization_result.value());
        REQUIRE(deserialization_result);
        REQUIRE(deserialization_result.value().is_int());
        REQUIRE(deserialization_result.value().as_int() == 9000000000LL);
    }

    SECTION("string roundtrips")
    {
        JsonValue original("round trip");
        auto serialization_result = serialization::Serializer<JsonValue>::serialize(original);
        REQUIRE(serialization_result);
        auto deserialization_result = serialization::Serializer<JsonValue>::deserialize(serialization_result.value());
        REQUIRE(deserialization_result);
        REQUIRE(deserialization_result.value().is_string());
        REQUIRE(deserialization_result.value().as_string() == "round trip");
    }

    SECTION("complex object roundtrips")
    {
        JsonValue original(JsonValue::Object{
            {"x", JsonValue(1)},
            {"y", JsonValue(JsonValue::Array{JsonValue(true), JsonValue("z")})},
        });
        auto serialization_result = serialization::Serializer<JsonValue>::serialize(original);
        REQUIRE(serialization_result);
        auto deserialization_result = serialization::Serializer<JsonValue>::deserialize(serialization_result.value());
        REQUIRE(deserialization_result);
        REQUIRE(deserialization_result.value().is_object());
        REQUIRE(deserialization_result.value()["x"].as_int() == 1);
        REQUIRE(deserialization_result.value()["y"].is_array());
        REQUIRE(deserialization_result.value()["y"][size_t{0}].as_bool() == true);
        REQUIRE(deserialization_result.value()["y"][size_t{1}].as_string() == "z");
    }
}

TEST_CASE("CheckedString serialization", "[serialization][checked_string]")
{
    SECTION("serializes as a JSON string")
    {
        Uuid v = Uuid::unchecked(std::string(valid_uuid));
        auto result = serialization::Serializer<decltype(v)>::serialize(v);
        REQUIRE(result);
        REQUIRE(result.value() == "\"550e8400-e29b-41d4-a716-446655440000\"");
    }
}

TEST_CASE("CheckedString deserialization", "[serialization][checked_string]")
{
    SECTION("deserializes from a valid UUID JSON string")
    {
        auto result = serialization::Serializer<Uuid>::deserialize("\"550e8400-e29b-41d4-a716-446655440000\"");
        REQUIRE(result);
        REQUIRE(result.value().view() == valid_uuid);
    }

    SECTION("returns error when UUID format is invalid")
    {
        auto result = serialization::Serializer<Uuid>::deserialize("\"not-a-valid-uuid\"");
        REQUIRE_FALSE(result);
        REQUIRE(result.error() == serialization::Error::invalid_value);
    }

    SECTION("returns error for empty string")
    {
        auto result = serialization::Serializer<Uuid>::deserialize(R"("")");
        REQUIRE_FALSE(result);
        REQUIRE(result.error() == serialization::Error::invalid_value);
    }
}

TEST_CASE("WriteTextFileRequest serialization", "[serialization][write_text_file_request]")
{
    SECTION("serializes required fields with correct key names")
    {
        WriteTextFileRequest req{
            .session_id = SessionId::unchecked("sess-1"),
            .path       = "/tmp/foo.txt",
            .content    = "hello",
        };
        auto result = serialization::Serializer<WriteTextFileRequest>::serialize(req);
        REQUIRE(result);
        auto parsed = serialization::Serializer<JsonValue>::deserialize(result.value());
        REQUIRE(parsed);
        REQUIRE(parsed.value()["sessionId"].as_string() == "sess-1");
        REQUIRE(parsed.value()["path"].as_string() == "/tmp/foo.txt");
        REQUIRE(parsed.value()["content"].as_string() == "hello");
    }

    SECTION("omits _meta key when metadata is absent")
    {
        WriteTextFileRequest req{
            .session_id = SessionId::unchecked("sess-1"),
            .path       = "/tmp/foo.txt",
            .content    = "hello",
        };
        auto result = serialization::Serializer<WriteTextFileRequest>::serialize(req);
        REQUIRE(result);
        auto parsed = serialization::Serializer<JsonValue>::deserialize(result.value());
        REQUIRE(parsed);
        REQUIRE(parsed.value().as_object().find("_meta") == parsed.value().as_object().end());
    }

    SECTION("serializes metadata under _meta key")
    {
        WriteTextFileRequest req{
            .session_id = SessionId::unchecked("sess-1"),
            .path       = "/tmp/foo.txt",
            .content    = "hello",
            .metadata   = JsonValue::Object{{"encoding", JsonValue("utf-8")}},
        };
        auto result = serialization::Serializer<WriteTextFileRequest>::serialize(req);
        REQUIRE(result);
        auto parsed = serialization::Serializer<JsonValue>::deserialize(result.value());
        REQUIRE(parsed);
        REQUIRE(parsed.value()["_meta"]["encoding"].as_string() == "utf-8");
    }
}

TEST_CASE("WriteTextFileRequest deserialization", "[serialization][write_text_file_request]")
{
    SECTION("deserializes required fields")
    {
        auto result = serialization::Serializer<WriteTextFileRequest>::deserialize(
            R"({"sessionId":"sess-1","path":"/tmp/foo.txt","content":"hello"})");
        REQUIRE(result);
        REQUIRE(result.value().session_id.view() == "sess-1");
        REQUIRE(result.value().path == "/tmp/foo.txt");
        REQUIRE(result.value().content == "hello");
        REQUIRE_FALSE(result.value().metadata.has_value());
    }

    SECTION("deserializes metadata from _meta key")
    {
        auto result = serialization::Serializer<WriteTextFileRequest>::deserialize(
            R"({"sessionId":"sess-2","path":"/a.txt","content":"x","_meta":{"encoding":"utf-8"}})");
        REQUIRE(result);
        REQUIRE(result.value().metadata.has_value());
        const auto& meta = result.value().metadata.value();
        REQUIRE(meta.at("encoding").as_string() == "utf-8");
    }

    SECTION("roundtrips without metadata")
    {
        WriteTextFileRequest original{
            .session_id = SessionId::unchecked("sess-rt"),
            .path       = "/round/trip.txt",
            .content    = "roundtrip content",
        };
        auto serialized = serialization::Serializer<WriteTextFileRequest>::serialize(original);
        REQUIRE(serialized);
        auto deserialized = serialization::Serializer<WriteTextFileRequest>::deserialize(serialized.value());
        REQUIRE(deserialized);
        REQUIRE(deserialized.value().session_id.view() == original.session_id.view());
        REQUIRE(deserialized.value().path == original.path);
        REQUIRE(deserialized.value().content == original.content);
        REQUIRE_FALSE(deserialized.value().metadata.has_value());
    }

    SECTION("roundtrips with metadata")
    {
        WriteTextFileRequest original{
            .session_id = SessionId::unchecked("sess-rt"),
            .path       = "/round/trip.txt",
            .content    = "roundtrip content",
            .metadata   = JsonValue::Object{{"key", JsonValue(42)}},
        };
        auto serialized = serialization::Serializer<WriteTextFileRequest>::serialize(original);
        REQUIRE(serialized);
        auto deserialized = serialization::Serializer<WriteTextFileRequest>::deserialize(serialized.value());
        REQUIRE(deserialized);
        REQUIRE(deserialized.value().metadata.has_value());
        REQUIRE(deserialized.value().metadata.value().at("key").as_int() == 42);
    }
}
