#pragma once

#include <string>

namespace PatchIt::Core
{
    #define MAKE_ERROR(code, msg) ::PatchIt::Core::Error(code, msg, __FILE__, __LINE__)

    enum class ErrorCode
    {
        None = 0,
        FileNotFound,
        FileSize,
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

        Error(const Error& other)
            : m_Code(other.m_Code), m_Message(other.m_Message), m_File(other.m_File), m_Line(other.m_Line) { }

        Error(Error&& other)
            : m_Code(std::move(other.m_Code)),
              m_Message(std::move(other.m_Message)),
              m_File(std::move(other.m_File)),
              m_Line(std::move(other.m_Line)) { }

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

        Result(Type&& value)
            : m_Value(std::move(value)), m_HasValue(true) { }
        
        Result(const Error& error)
            : m_Error(error), m_HasValue(false) { }

        Result(Error&& error)
            : m_Error(std::move(error)), m_HasValue(false) { }

        Result(const Result& other)
            : m_Value(other.m_Value), m_Error(other.m_Error), m_HasValue(other.m_HasValue) { }

        Result(Result&& other)
            : m_Value(std::move(other.m_Value)),
              m_Error(std::move(other.m_Error)),
              m_HasValue(std::move(other.m_HasValue)) { }

        bool HasValue() const
        {
            return m_HasValue;
        }

        const Type& GetValue() const
        {
            return m_Value;
        }

        const Type& GetValueOr(const Type& other) const
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
