#pragma once

#include <string>

namespace culpeo::acp::util
{
    template<typename Policy>
    class CheckedString
    {
        bool m_valid;
        std::string m_value;
        struct unchecked_tag { explicit unchecked_tag() = default; };

        CheckedString(unchecked_tag, std::string value) : m_valid{true}, m_value{ std::move(value) } {}
    public:
        CheckedString() : m_valid{false}, m_value{} {}

        explicit CheckedString(std::string value) : m_valid{Policy::validate(value)}, m_value{ std::move(value) } {
        }

        static CheckedString unchecked(std::string value) {
            return CheckedString(unchecked_tag{}, std::move(value));
        }

        bool valid() const noexcept {
            return m_valid;
        }

        [[nodiscard]] const std::string& get() const & noexcept { return m_value; }
        [[nodiscard]] std::string get() && noexcept { return std::move(m_value); }
        [[nodiscard]] const char* c_str() const noexcept { return m_value.c_str(); }

        [[nodiscard]] std::string_view view() const noexcept { return m_value; }
        [[nodiscard]] const std::string& str() const & noexcept { return m_value; }
        [[nodiscard]] std::string str() && noexcept { return std::move(m_value); }

        friend auto operator<=>(const CheckedString& lhs, const CheckedString& rhs) noexcept = default;
        friend bool operator==(const CheckedString& lhs, const CheckedString& rhs) noexcept = default;
    };
}