#ifndef LOG_HPP_
#define LOG_HPP_

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>

#if !defined SPDLOG_VER_MAJOR
namespace spdlog
{
    typedef char const *string_view_t;

    static std::shared_ptr<spdlog::logger> dlog;

    std::shared_ptr<spdlog::logger> default_logger() { return dlog; }

    inline spdlog::logger *default_logger_raw()
    {
        return dlog.get();
    }

    inline void set_default_logger(std::shared_ptr<spdlog::logger> default_logger)
    {
        dlog = default_logger;
    }

#if 0
    template<typename... Args>
    inline void log(source_loc source, level::level_enum lvl, string_view_t fmt, const Args &... args)
    {
        default_logger_raw()->log(source, lvl, fmt, args...);
    }

    template<typename... Args>
    inline void log(level::level_enum lvl, string_view_t fmt, const Args &... args)
    {
        default_logger_raw()->log(source_loc{}, lvl, fmt, args...);
    }
#endif

    template<typename... Args>
    inline void trace(string_view_t fmt, const Args &... args)
    {
        default_logger_raw()->trace(fmt, args...);
    }

    template<typename... Args>
    inline void debug(string_view_t fmt, const Args &... args)
    {
        default_logger_raw()->debug(fmt, args...);
    }

    template<typename... Args>
    inline void info(string_view_t fmt, const Args &... args)
    {
        default_logger_raw()->info(fmt, args...);
    }

    template<typename... Args>
    inline void warn(string_view_t fmt, const Args &... args)
    {
        default_logger_raw()->warn(fmt, args...);
    }

    template<typename... Args>
    inline void error(string_view_t fmt, const Args &... args)
    {
        default_logger_raw()->error(fmt, args...);
    }

    template<typename... Args>
    inline void critical(string_view_t fmt, const Args &... args)
    {
        default_logger_raw()->critical(fmt, args...);
    }

#if 0
    template<typename T>
    inline void log(source_loc source, level::level_enum lvl, const T &msg)
    {
        default_logger_raw()->log(source, lvl, msg);
    }
#endif

    template<typename T>
    inline void log(level::level_enum lvl, const T &msg)
    {
        default_logger_raw()->log(lvl, msg);
    }

    template<typename T>
    inline void trace(const T &msg)
    {
        default_logger_raw()->trace(msg);
    }

    template<typename T>
    inline void debug(const T &msg)
    {
        default_logger_raw()->debug(msg);
    }

    template<typename T>
    inline void info(const T &msg)
    {
        default_logger_raw()->info(msg);
    }

    template<typename T>
    inline void warn(const T &msg)
    {
        default_logger_raw()->warn(msg);
    }

    template<typename T>
    inline void error(const T &msg)
    {
        default_logger_raw()->error(msg);
    }

    template<typename T>
    inline void critical(const T &msg)
    {
        default_logger_raw()->critical(msg);
    }

#ifdef SPDLOG_WCHAR_TO_UTF8_SUPPORT
    template<typename... Args>
    inline void log(source_loc source, level::level_enum lvl, wstring_view_t fmt, const Args &... args)
    {
        default_logger_raw()->log(source, lvl, fmt, args...);
    }

    template<typename... Args>
    inline void log(level::level_enum lvl, wstring_view_t fmt, const Args &... args)
    {
        default_logger_raw()->log(lvl, fmt, args...);
    }

    template<typename... Args>
    inline void trace(wstring_view_t fmt, const Args &... args)
    {
        default_logger_raw()->trace(fmt, args...);
    }

    template<typename... Args>
    inline void debug(wstring_view_t fmt, const Args &... args)
    {
        default_logger_raw()->debug(fmt, args...);
    }

    template<typename... Args>
    inline void info(wstring_view_t fmt, const Args &... args)
    {
        default_logger_raw()->info(fmt, args...);
    }

    template<typename... Args>
    inline void warn(wstring_view_t fmt, const Args &... args)
    {
        default_logger_raw()->warn(fmt, args...);
    }

    template<typename... Args>
    inline void error(wstring_view_t fmt, const Args &... args)
    {
        default_logger_raw()->error(fmt, args...);
    }

    template<typename... Args>
    inline void critical(wstring_view_t fmt, const Args &... args)
    {
        default_logger_raw()->critical(fmt, args...);
    }

#endif // SPDLOG_WCHAR_TO_UTF8_SUPPORT    
}
#endif

#endif
