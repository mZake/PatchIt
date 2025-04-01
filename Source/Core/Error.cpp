#include <format>

#include "Error.hpp"

namespace PatchIt
{
    bool Error::HasError() const
    {
        return m_Code != ErrorCode::None;
    }

    std::string Error::ToString() const
    {
        return std::format("[{}:{}] Error {}: {}", m_File, m_Line, static_cast<int>(m_Code), m_Message);
    }
}
