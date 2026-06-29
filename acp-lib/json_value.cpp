#include <acp/util/json_value.hpp>

using namespace culpeo::acp;

bool util::JsonValue::as_bool() const noexcept
{

    return std::get<bool>(m_value);
}

int64_t util::JsonValue::as_int() const noexcept
{
    return std::get<int64_t>(m_value);
}

double util::JsonValue::as_double() const noexcept
{
    return std::get<double>(m_value);
}

const std::string& util::JsonValue::as_string() const & noexcept
{
    return std::get<std::string>(m_value);
}

std::string& util::JsonValue::as_string() & noexcept
{
    return std::get<std::string>(m_value);
}

std::string&& util::JsonValue::as_string() && noexcept
{
    return std::get<std::string>(std::move(m_value));
}

const util::JsonValue::Array& util::JsonValue::as_array() const & noexcept
{
    return std::get<Array>(m_value);
}

util::JsonValue::Array& util::JsonValue::as_array() & noexcept
{
    return std::get<Array>(m_value);
}

util::JsonValue::Array&& util::JsonValue::as_array() && noexcept
{
    return std::get<Array>(std::move(m_value));
}

const util::JsonValue::Object& util::JsonValue::as_object() const & noexcept
{
    return std::get<Object>(m_value);
}

util::JsonValue::Object& util::JsonValue::as_object() & noexcept
{
    return std::get<Object>(m_value);
}

util::JsonValue::Object&& util::JsonValue::as_object() && noexcept
{
    return std::get<Object>(std::move(m_value));
}

const util::JsonValue& util::JsonValue::operator[](std::string_view key) const & noexcept
{
    const auto it = as_object().find(key);
    return it->second;
}

util::JsonValue& util::JsonValue::operator[](std::string_view key) & noexcept
{
    return as_object().find(key)->second;
}

util::JsonValue&& util::JsonValue::operator[](std::string_view key) && noexcept
{
    return std::move(as_object().find(key)->second);
}

const util::JsonValue& util::JsonValue::operator[](size_t index) const & noexcept
{
    return as_array().at(index);
}

util::JsonValue& util::JsonValue::operator[](size_t index) & noexcept
{
    return as_array().at(index);
}

util::JsonValue&& util::JsonValue::operator[](size_t index) && noexcept
{
    return std::move(as_array().at(index));
}