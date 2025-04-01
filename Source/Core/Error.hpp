#pragma once

#include <string>

namespace PatchIt
{
    #define MAKE_ERROR(code, msg) Error(code, msg, __FILE__, __LINE__)

    enum class ErrorCode
    {
        None = 0,
        FileNotFound,
        ReadError,
        InvalidFormat,
        BadAlloc,
    };

    class Error
    {
    public:
        Error() = default;
        Error(ErrorCode code, const std::string& message, const std::string& file, int line)
            : m_Code(code), m_Message(message), m_File(file), m_Line(line) { }

        bool HasError() const;
        std::string ToString() const;

    private:
        ErrorCode m_Code = ErrorCode::None;
        std::string m_Message = "Unknow";
        std::string m_File = "Unknow";
        int m_Line = 0;
    };

    template <typename Type>
    class Result
    {
    public:
        Result(const Type& value)
            : m_Value(value), m_HasValue(true) { }
        Result(const Error& error)
            : m_Error(error), m_HasValue(false) { }

        bool HasValue() const
        {
            return m_HasValue;
        }

        const Type& GetValue() const
        {
            return m_Value;
        }

        const Type& GetValueOr(const Type& other)
        {
            return m_HasValue ? m_Value : other;
        }

        const Error& GetError() const
        {
            return m_Error;
        }

    private:
        bool m_HasValue;
        Error m_Error;
        Type m_Value;
    };
}
