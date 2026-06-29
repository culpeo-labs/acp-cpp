#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <acp/util/json_value.hpp>

using namespace culpeo::acp::util;

TEST_CASE("JsonValue construction and type checking", "[json_value]")
{
    SECTION("default constructor is null")
    {
        JsonValue v;
        REQUIRE(v.is_null());
        REQUIRE_FALSE(v.is_bool());
        REQUIRE_FALSE(v.is_int());
        REQUIRE_FALSE(v.is_double());
        REQUIRE_FALSE(v.is_string());
        REQUIRE_FALSE(v.is_array());
        REQUIRE_FALSE(v.is_object());
    }

    SECTION("nullptr_t constructor is null")
    {
        JsonValue v(nullptr);
        REQUIRE(v.is_null());
    }

    SECTION("bool constructor")
    {
        JsonValue t(true);
        REQUIRE(t.is_bool());
        REQUIRE(t.as_bool() == true);

        JsonValue f(false);
        REQUIRE(f.is_bool());
        REQUIRE(f.as_bool() == false);
    }

    SECTION("integral constructor stores as int64_t")
    {
        JsonValue v(42);
        REQUIRE(v.is_int());
        REQUIRE(v.as_int() == 42);

        JsonValue neg(-7);
        REQUIRE(neg.is_int());
        REQUIRE(neg.as_int() == -7);

        JsonValue large(int64_t{9000000000LL});
        REQUIRE(large.is_int());
        REQUIRE(large.as_int() == 9000000000LL);
    }

    SECTION("bool is not treated as integral")
    {
        JsonValue v(true);
        REQUIRE(v.is_bool());
        REQUIRE_FALSE(v.is_int());
    }

    SECTION("floating point constructor stores as double")
    {
        JsonValue v(3.14);
        REQUIRE(v.is_double());
        REQUIRE_THAT(v.as_double(), Catch::Matchers::WithinULP(3.14, 1));

        JsonValue vf(2.5f);
        REQUIRE(vf.is_double());
    }

    SECTION("const char* constructor")
    {
        JsonValue v("hello");
        REQUIRE(v.is_string());
        REQUIRE(v.as_string() == "hello");
    }

    SECTION("std::string constructor (copy)")
    {
        std::string s = "world";
        JsonValue v(s);
        REQUIRE(v.is_string());
        REQUIRE(v.as_string() == "world");
    }

    SECTION("std::string constructor (move)")
    {
        std::string s = "moved";
        JsonValue v(std::move(s));
        REQUIRE(v.is_string());
        REQUIRE(v.as_string() == "moved");
    }

    SECTION("Array constructor (copy)")
    {
        JsonValue::Array arr = {JsonValue(1), JsonValue(2), JsonValue(3)};
        JsonValue v(arr);
        REQUIRE(v.is_array());
        REQUIRE(v.as_array().size() == 3);
    }

    SECTION("Array constructor (move)")
    {
        JsonValue::Array arr = {JsonValue("a"), JsonValue("b")};
        JsonValue v(std::move(arr));
        REQUIRE(v.is_array());
        REQUIRE(v.as_array().size() == 2);
    }

    SECTION("Object constructor (copy)")
    {
        JsonValue::Object obj = {{"key", JsonValue(99)}};
        JsonValue v(obj);
        REQUIRE(v.is_object());
        REQUIRE(v.as_object().size() == 1);
    }

    SECTION("Object constructor (move)")
    {
        JsonValue::Object obj = {{"x", JsonValue(true)}};
        JsonValue v(std::move(obj));
        REQUIRE(v.is_object());
        REQUIRE(v.as_object().size() == 1);
    }
}

TEST_CASE("JsonValue assignment operators", "[json_value]")
{
    JsonValue v;

    SECTION("assign nullptr")
    {
        v = 42;
        v = nullptr;
        REQUIRE(v.is_null());
    }

    SECTION("assign bool")
    {
        v = true;
        REQUIRE(v.is_bool());
        REQUIRE(v.as_bool() == true);
    }

    SECTION("assign integral")
    {
        v = 100;
        REQUIRE(v.is_int());
        REQUIRE(v.as_int() == 100);
    }

    SECTION("assign double")
    {
        v = 1.5;
        REQUIRE(v.is_double());
        REQUIRE_THAT(v.as_double(), Catch::Matchers::WithinULP(1.5, 1));
    }

    SECTION("assign const char*")
    {
        v = "test";
        REQUIRE(v.is_string());
        REQUIRE(v.as_string() == "test");
    }

    SECTION("assign std::string copy")
    {
        std::string s = "copy";
        v = s;
        REQUIRE(v.is_string());
        REQUIRE(v.as_string() == "copy");
    }

    SECTION("assign std::string move")
    {
        std::string s = "move";
        v = std::move(s);
        REQUIRE(v.is_string());
        REQUIRE(v.as_string() == "move");
    }

    SECTION("assign Array copy")
    {
        JsonValue::Array arr = {JsonValue(1)};
        v = arr;
        REQUIRE(v.is_array());
    }

    SECTION("assign Array move")
    {
        JsonValue::Array arr = {JsonValue(2)};
        v = std::move(arr);
        REQUIRE(v.is_array());
    }

    SECTION("assign Object copy")
    {
        JsonValue::Object obj = {{"k", JsonValue(3)}};
        v = obj;
        REQUIRE(v.is_object());
    }

    SECTION("assign Object move")
    {
        JsonValue::Object obj = {{"k", JsonValue(4)}};
        v = std::move(obj);
        REQUIRE(v.is_object());
    }
}

TEST_CASE("JsonValue as_string overloads", "[json_value]")
{
    SECTION("const lvalue ref")
    {
        const JsonValue v("hello");
        const std::string& s = v.as_string();
        REQUIRE(s == "hello");
    }

    SECTION("lvalue ref allows mutation")
    {
        JsonValue v("hello");
        v.as_string() += " world";
        REQUIRE(v.as_string() == "hello world");
    }

    SECTION("rvalue ref moves out")
    {
        JsonValue v("rvalue");
        std::string s = std::move(v).as_string();
        REQUIRE(s == "rvalue");
    }
}

TEST_CASE("JsonValue as_array overloads", "[json_value]")
{
    SECTION("const lvalue ref")
    {
        const JsonValue v(JsonValue::Array{JsonValue(1), JsonValue(2)});
        const JsonValue::Array& arr = v.as_array();
        REQUIRE(arr.size() == 2);
    }

    SECTION("lvalue ref allows mutation")
    {
        JsonValue v(JsonValue::Array{JsonValue(1)});
        v.as_array().push_back(JsonValue(2));
        REQUIRE(v.as_array().size() == 2);
    }

    SECTION("rvalue ref moves out")
    {
        JsonValue v(JsonValue::Array{JsonValue(10)});
        JsonValue::Array arr = std::move(v).as_array();
        REQUIRE(arr.size() == 1);
    }
}

TEST_CASE("JsonValue as_object overloads", "[json_value]")
{
    SECTION("const lvalue ref")
    {
        const JsonValue v(JsonValue::Object{{"a", JsonValue(1)}});
        const JsonValue::Object& obj = v.as_object();
        REQUIRE(obj.size() == 1);
    }

    SECTION("lvalue ref allows mutation")
    {
        JsonValue v(JsonValue::Object{{"a", JsonValue(1)}});
        v.as_object()["b"] = JsonValue(2);
        REQUIRE(v.as_object().size() == 2);
    }

    SECTION("rvalue ref moves out")
    {
        JsonValue v(JsonValue::Object{{"x", JsonValue(5)}});
        JsonValue::Object obj = std::move(v).as_object();
        REQUIRE(obj.size() == 1);
    }
}

TEST_CASE("JsonValue operator[] by string key", "[json_value]")
{
    JsonValue::Object obj = {
        {"name", JsonValue("alice")},
        {"age",  JsonValue(30)},
    };

    SECTION("const lvalue ref")
    {
        const JsonValue v(obj);
        REQUIRE(v["name"].as_string() == "alice");
        REQUIRE(v["age"].as_int() == 30);
    }

    SECTION("lvalue ref allows mutation")
    {
        JsonValue v(obj);
        v["age"] = JsonValue(31);
        REQUIRE(v["age"].as_int() == 31);
    }

    SECTION("rvalue ref moves value out")
    {
        JsonValue v(obj);
        JsonValue name = std::move(v)["name"];
        REQUIRE(name.as_string() == "alice");
    }
}

TEST_CASE("JsonValue operator[] by index", "[json_value]")
{
    JsonValue::Array arr = {JsonValue(10), JsonValue(20), JsonValue(30)};

    SECTION("const lvalue ref")
    {
        const JsonValue v(arr);
        REQUIRE(v[0].as_int() == 10);
        REQUIRE(v[2].as_int() == 30);
    }

    SECTION("lvalue ref allows mutation")
    {
        JsonValue v(arr);
        v[1] = JsonValue(99);
        REQUIRE(v[1].as_int() == 99);
    }

    SECTION("rvalue ref moves value out")
    {
        JsonValue v(arr);
        JsonValue elem = std::move(v)[0];
        REQUIRE(elem.as_int() == 10);
    }
}

TEST_CASE("JsonValue nested structures", "[json_value]")
{
    SECTION("object containing array")
    {
        JsonValue::Object obj = {
            {"items", JsonValue(JsonValue::Array{JsonValue(1), JsonValue(2), JsonValue(3)})}
        };
        JsonValue v(obj);
        REQUIRE(v["items"].is_array());
        REQUIRE(v["items"][size_t{0}].as_int() == 1);
        REQUIRE(v["items"][size_t{2}].as_int() == 3);
    }

    SECTION("array containing objects")
    {
        JsonValue::Array arr = {
            JsonValue(JsonValue::Object{{"x", JsonValue(1)}}),
            JsonValue(JsonValue::Object{{"x", JsonValue(2)}}),
        };
        JsonValue v(arr);
        REQUIRE(v[size_t{0}]["x"].as_int() == 1);
        REQUIRE(v[size_t{1}]["x"].as_int() == 2);
    }
}
