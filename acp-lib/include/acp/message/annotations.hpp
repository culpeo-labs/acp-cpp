#include <optional>
#include <vector>

#include <nlohmann/json.hpp>

#include <acp/message/role.hpp>

namespace culpeo::acp::message
{
    struct Annotations
    {
        std::optional<std::vector<Role>> audience;
        std::optional<std::string> last_modified;
        std::optional<double> priority;
        std::optional<nlohmann::json> meta;
    };
}