#include "logging.h"
#include <spdlog/spdlog.h>

//-----------------------------------------------------------------------------
std::string extract_name(const char* file)
{
    std::string name = file;
    std::string::size_type pos = name.find_last_of("/\\");

    return (pos != std::string::npos) ? name.substr(pos + 1) : name;
}

//-----------------------------------------------------------------------------
void replace_all(std::string& str, const std::string& src, const std::string& dst)
{
    std::string::size_type pos = 0;
    std::string::size_type src_size = src.size();
    std::string::size_type dst_size = dst.size();
    while ((pos = str.find(src, pos)) != std::string::npos)
    {
        str.replace(pos, src_size, dst);
        pos += dst_size;
    }
}

//-----------------------------------------------------------------------------
std::string& unbrace(std::string& msg)
{
    replace_all(msg, "{", "{{");
    replace_all(msg, "}", "}}");

    return msg;
}

//-----------------------------------------------------------------------------
int spdlog_get(const char* logger_name)
{
    std::shared_ptr<spdlog::logger> logger_ptr = spdlog::get(logger_name);

    return (logger_ptr != nullptr) ? 1 : 0;
}

//-----------------------------------------------------------------------------
void spdlog_set_pattern(const char* format_string)
{
    spdlog::set_pattern(format_string);
}

//-----------------------------------------------------------------------------
void spdlog_set_level(int log_level)
{
    spdlog::set_level(static_cast<spdlog::level::level_enum>(log_level));
}

//-----------------------------------------------------------------------------
void spdlog_set_async_mode(size_t queue_size)
{
    spdlog::set_async_mode(queue_size);
}

//-----------------------------------------------------------------------------
void spdlog_set_sync_mode()
{
    spdlog::set_sync_mode();
}

//-----------------------------------------------------------------------------
void spdlog_basic_logger_mt(const char* logger_name, const char* filename, int truncate)
{
    spdlog::basic_logger_mt(logger_name, filename, (truncate == 0) ? false : true);
}

//-----------------------------------------------------------------------------
void spdlog_basic_logger_st(const char* logger_name, const char* filename, int truncate)
{
    spdlog::basic_logger_st(logger_name, filename, (truncate == 0) ? false : true);
}

//-----------------------------------------------------------------------------
void spdlog_rotating_logger_mt(const char* logger_name, const char* filename, size_t max_file_size, size_t max_files)
{
    spdlog::rotating_logger_mt(logger_name, filename, max_file_size, max_files);
}

//-----------------------------------------------------------------------------
void spdlog_rotating_logger_st(const char* logger_name, const char* filename, size_t max_file_size, size_t max_files)
{
    spdlog::rotating_logger_st(logger_name, filename, max_file_size, max_files);
}

//-----------------------------------------------------------------------------
void spdlog_daily_logger_mt(const char* logger_name, const char* filename, int hour, int minute)
{
    spdlog::daily_logger_mt(logger_name, filename, hour, minute);
}

//-----------------------------------------------------------------------------
void spdlog_daily_logger_st(const char* logger_name, const char* filename, int hour, int minute)
{
    spdlog::daily_logger_st(logger_name, filename, hour, minute);
}

//-----------------------------------------------------------------------------
void spdlog_stdout_logger_mt(const char* logger_name)
{
    spdlog::stdout_logger_mt(logger_name);
}

//-----------------------------------------------------------------------------
void spdlog_stdout_logger_st(const char* logger_name)
{
    spdlog::stdout_logger_st(logger_name);
}

//-----------------------------------------------------------------------------
void spdlog_stderr_logger_mt(const char* logger_name)
{
    spdlog::stderr_logger_mt(logger_name);
}

//-----------------------------------------------------------------------------
void spdlog_stderr_logger_st(const char* logger_name)
{
    spdlog::stderr_logger_st(logger_name);
}

//-----------------------------------------------------------------------------
void spdlog_stdout_color_mt(const char* logger_name)
{
    spdlog::stdout_color_mt(logger_name);
}

//-----------------------------------------------------------------------------
void spdlog_stdout_color_st(const char* logger_name)
{
    spdlog::stdout_color_st(logger_name);
}

//-----------------------------------------------------------------------------
void spdlog_stderr_color_mt(const char* logger_name)
{
    spdlog::stderr_color_mt(logger_name);
}

//-----------------------------------------------------------------------------
void spdlog_stderr_color_st(const char* logger_name)
{
    spdlog::stderr_color_st(logger_name);
}

//-----------------------------------------------------------------------------
void spdlog_syslog_logger(const char* logger_name, const char* ident, int syslog_option)
{
#ifdef SPDLOG_ENABLE_SYSLOG
    spdlog::syslog_logger(logger_name, ident, syslog_option);
#endif
}

//-----------------------------------------------------------------------------
void spdlog_drop(const char* logger_name)
{
    spdlog::drop(logger_name);
}

//-----------------------------------------------------------------------------
void spdlog_drop_all()
{
    spdlog::drop_all();
}

//-----------------------------------------------------------------------------
void spdlog_set_logger_level(const char* logger_name, int log_level)
{
    std::shared_ptr<spdlog::logger> logger_ptr = spdlog::get(logger_name);
    if (logger_ptr != nullptr)
    {
        logger_ptr->set_level(static_cast<spdlog::level::level_enum>(log_level));
    }
}

//-----------------------------------------------------------------------------
int spdlog_get_logger_level(const char* logger_name)
{
    std::shared_ptr<spdlog::logger> logger_ptr = spdlog::get(logger_name);
    if (logger_ptr != nullptr)
    {
        return static_cast<int>(logger_ptr->level());
    }

    return -1;
}

//-----------------------------------------------------------------------------
void spdlog_set_logger_pattern(const char* logger_name, const char* format_string)
{
    std::shared_ptr<spdlog::logger> logger_ptr = spdlog::get(logger_name);
    if (logger_ptr != nullptr)
    {
        return logger_ptr->set_pattern(format_string);
    }
}

//-----------------------------------------------------------------------------
void spdlog_logger_flush_on(const char* logger_name, int log_level)
{
    std::shared_ptr<spdlog::logger> logger_ptr = spdlog::get(logger_name);
    if (logger_ptr != nullptr)
    {
        logger_ptr->flush_on(static_cast<spdlog::level::level_enum>(log_level));
    }
}

//-----------------------------------------------------------------------------
void spdlog_logger_flush(const char* logger_name)
{
    std::shared_ptr<spdlog::logger> logger_ptr = spdlog::get(logger_name);
    if (logger_ptr != nullptr)
    {
        logger_ptr->flush();
    }
}

//-----------------------------------------------------------------------------
void spdlog_logger_log(const char* logger_name, int log_level, const char* msg)
{
    std::shared_ptr<spdlog::logger> logger_ptr = spdlog::get(logger_name);
    if (logger_ptr != nullptr)
    {
        if (!logger_ptr->should_log(static_cast<spdlog::level::level_enum>(log_level))) return;
        
#ifdef UNBRACE_MSG
        std::string str_msg = msg;
        str_msg = unbrace(str_msg);
        logger_ptr->log(static_cast<spdlog::level::level_enum>(log_level), str_msg);
#else
        logger_ptr->log(static_cast<spdlog::level::level_enum>(log_level), msg);
#endif
    }
}

//-----------------------------------------------------------------------------
void spdlog_logger_log_var(const char* logger_name, int log_level, const char* fmt, ...)
{
    std::shared_ptr<spdlog::logger> logger_ptr = spdlog::get(logger_name);
    if (logger_ptr != nullptr)
    {
        if (!logger_ptr->should_log(static_cast<spdlog::level::level_enum>(log_level))) return;
        
        char msg[MSG_BUF_MAX_LEN];

        va_list args;
        va_start(args, fmt);
        vsnprintf(msg, sizeof(msg), fmt, args);
        va_end(args);

#ifdef UNBRACE_MSG
        std::string str_msg = msg;
        str_msg = unbrace(str_msg);
        logger_ptr->log(static_cast<spdlog::level::level_enum>(log_level), str_msg);
#else
        logger_ptr->log(static_cast<spdlog::level::level_enum>(log_level), msg);
#endif
    }
}

//-----------------------------------------------------------------------------
void spdlog_logger_log_ffl(const char* logger_name, int log_level, const char* func, const char* file, size_t line, int error_code, const char* msg)
{
    std::shared_ptr<spdlog::logger> logger_ptr = spdlog::get(logger_name);
    if (logger_ptr != nullptr)
    {
        if (!logger_ptr->should_log(static_cast<spdlog::level::level_enum>(log_level))) return;
        
        std::string str_msg = msg;
#ifdef UNBRACE_MSG
        str_msg = unbrace(str_msg);
#endif
        str_msg = ((error_code != LOG_SUCCESS) ? ("ErrorCode: " + std::to_string(error_code) + ", ") : "") + str_msg + LOG_SUFFIX_STR;

        logger_ptr->log(static_cast<spdlog::level::level_enum>(log_level), str_msg.c_str(), func, extract_name(file).c_str(), line);
    }
}

//-----------------------------------------------------------------------------
void spdlog_logger_log_ffl_var(const char* logger_name, int log_level, const char* func, const char* file, size_t line, int error_code, const char* fmt, ...)
{
    std::shared_ptr<spdlog::logger> logger_ptr = spdlog::get(logger_name);
    if (logger_ptr != nullptr)
    {
        if (!logger_ptr->should_log(static_cast<spdlog::level::level_enum>(log_level))) return;
        
        char msg[MSG_BUF_MAX_LEN];

        va_list args;
        va_start(args, fmt);
        vsnprintf(msg, sizeof(msg), fmt, args);
        va_end(args);

        std::string str_msg = msg;
#ifdef UNBRACE_MSG
        str_msg = unbrace(str_msg);
#endif
        str_msg = ((error_code != LOG_SUCCESS) ? ("ErrorCode: " + std::to_string(error_code) + ", ") : "") + str_msg + LOG_SUFFIX_STR;

        logger_ptr->log(static_cast<spdlog::level::level_enum>(log_level), str_msg.c_str(), func, extract_name(file).c_str(), line);
    }
}
