//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//
// Copyright(c) 2017 zhishupp.
// <spdlog> C wrapper for support: __FUNCTION__,  __FILE__, __LINE__
//-----------------------------------------------------------------------------
#ifndef __LOGGING_H_
#define __LOGGING_H_

//-----------------------------------------------------------------------------
#ifdef WIN32
#define __DLL_EXPORT_ __declspec(dllexport)
#else
#define __DLL_EXPORT_ __attribute__((visibility ("default")))
#endif

//-----------------------------------------------------------------------------
#ifdef __cplusplus
#define __EXTERN_C_ extern "C"
#else
#define __EXTERN_C_
#endif

//-----------------------------------------------------------------------------
#include <stdio.h>

//-----------------------------------------------------------------------------
#define MSG_MAX_BUF_LEN     2048
#define LOG_SUFFIX_STR      " [{}|{}:{}]"
#define LOG_SUCCESS         0
#define METHOD_ERROR        "Call function return error: "
#define UNBRACE_MSG         1

//-----------------------------------------------------------------------------
#define spdlog_trace        0
#define spdlog_debug        1
#define spdlog_info         2
#define spdlog_warn         3
#define spdlog_error        4
#define spdlog_criti        5
#define spdlog_off          6

//-----------------------------------------------------------------------------
//
// if logger with such name exists, will return 1, else will return 0
//
__EXTERN_C_ __DLL_EXPORT_ int spdlog_get(const char* logger_name);

//-----------------------------------------------------------------------------
//
// Set global formatting
// example: spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %l : %v");
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_set_pattern(const char* format_string);

//-----------------------------------------------------------------------------
//
// Set global logging level for
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_set_level(int log_level);

//-----------------------------------------------------------------------------
//
// Turn on async mode (off by default) and set the queue size for each async_logger.
// effective only for loggers created after this call.
// queue_size: size of queue (must be power of 2):
//    Each logger will pre-allocate a dedicated queue with queue_size entries upon construction.
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_set_async_mode(size_t queue_size);

//-----------------------------------------------------------------------------
//
// Turn off async mode
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_set_sync_mode();

//-----------------------------------------------------------------------------
//
// Create and register multi/single threaded basic file logger.
// Basic logger simply writes to given file without any limitatons or rotations.
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_basic_logger_mt(const char* logger_name, const char* filename, int truncate);
__EXTERN_C_ __DLL_EXPORT_ void spdlog_basic_logger_st(const char* logger_name, const char* filename, int truncate);

//-----------------------------------------------------------------------------
//
// Create and register multi/single threaded rotating file logger
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_rotating_logger_mt(const char* logger_name, const char* filename, size_t max_file_size, size_t max_files);
__EXTERN_C_ __DLL_EXPORT_ void spdlog_rotating_logger_st(const char* logger_name, const char* filename, size_t max_file_size, size_t max_files);

//-----------------------------------------------------------------------------
//
// Create file logger which creates new file on the given time (default in  midnight):
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_daily_logger_mt(const char* logger_name, const char* filename, int hour, int minute);
__EXTERN_C_ __DLL_EXPORT_ void spdlog_daily_logger_st(const char* logger_name, const char* filename, int hour, int minute);

//-----------------------------------------------------------------------------
//
// Create and register stdout/stderr loggers
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_stdout_logger_mt(const char* logger_name);
__EXTERN_C_ __DLL_EXPORT_ void spdlog_stdout_logger_st(const char* logger_name);
__EXTERN_C_ __DLL_EXPORT_ void spdlog_stderr_logger_mt(const char* logger_name);
__EXTERN_C_ __DLL_EXPORT_ void spdlog_stderr_logger_st(const char* logger_name);

//-----------------------------------------------------------------------------
//
// Create and register colored stdout/stderr loggers
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_stdout_color_mt(const char* logger_name);
__EXTERN_C_ __DLL_EXPORT_ void spdlog_stdout_color_st(const char* logger_name);
__EXTERN_C_ __DLL_EXPORT_ void spdlog_stderr_color_mt(const char* logger_name);
__EXTERN_C_ __DLL_EXPORT_ void spdlog_stderr_color_st(const char* logger_name);

//-----------------------------------------------------------------------------
//
// Create and register a syslog logger
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_syslog_logger(const char* logger_name, const char* ident, int syslog_option);

//-----------------------------------------------------------------------------
//
// Drop the reference to the given logger
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_drop(const char* logger_name);

//-----------------------------------------------------------------------------
//
// Drop all references from the registry
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_drop_all();

//-----------------------------------------------------------------------------
//
// Set a logger's level
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_set_logger_level(const char* logger_name, int log_level);

//-----------------------------------------------------------------------------
//
// Get a logger's level
//
__EXTERN_C_ __DLL_EXPORT_ int spdlog_get_logger_level(const char* logger_name);

//-----------------------------------------------------------------------------
//
// Set a logger's pattern
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_set_logger_pattern(const char* logger_name, const char* format_string);

//-----------------------------------------------------------------------------
//
// Set a logger's flush on
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_logger_flush_on(const char* logger_name, int log_level);

//-----------------------------------------------------------------------------
//
// Flush a logger
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_logger_flush(const char* logger_name);

//-----------------------------------------------------------------------------
//
// Logger logging message
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_logger_log(const char* logger_name, int log_level, const char* msg);

//-----------------------------------------------------------------------------
//
// Logger logging variadic message
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_logger_log_var(const char* logger_name, int log_level, const char* fmt, ...);

//-----------------------------------------------------------------------------
//
// Logger logging message with __FUNCTION__,  __FILE__, __LINE__
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_logger_log_ffl(const char* logger_name, int log_level, const char* func, const char* file, size_t line, int error_code, const char* msg);

//-----------------------------------------------------------------------------
//
// Logger logging variadic message with __FUNCTION__,  __FILE__, __LINE__
//
__EXTERN_C_ __DLL_EXPORT_ void spdlog_logger_log_ffl_var(const char* logger_name, int log_level, const char* func, const char* file, size_t line, int error_code, const char* fmt, ...);

//-----------------------------------------------------------------------------
//
// Logger macro
//
//-----------------------------------------------------------------------------
// trace function, for enter a function
#define TRACE_FUNCTION(name) \
    spdlog_logger_log_ffl(name, spdlog_trace, __FUNCTION__, __FILE__, __LINE__, LOG_SUCCESS, "==>")

//-----------------------------------------------------------------------------
// trace logging
#define LOG_TRACE(name, message) \
    spdlog_logger_log_ffl(name, spdlog_trace, __FUNCTION__, __FILE__, __LINE__, LOG_SUCCESS, message)

//-----------------------------------------------------------------------------
// debug logging
#define LOG_DEBUG(name, message) \
    spdlog_logger_log_ffl(name, spdlog_debug, __FUNCTION__, __FILE__, __LINE__, LOG_SUCCESS, message)

//-----------------------------------------------------------------------------
// info logging
#define LOG_INFO(name, message) \
    spdlog_logger_log_ffl(name, spdlog_info, __FUNCTION__, __FILE__, __LINE__, LOG_SUCCESS, message)

//-----------------------------------------------------------------------------
// warn logging
#define LOG_WARN(name, message) \
    spdlog_logger_log_ffl(name, spdlog_warn, __FUNCTION__, __FILE__, __LINE__, LOG_SUCCESS, message)

//-----------------------------------------------------------------------------
// error logging
#define LOG_ERROR(name, errcode, message) \
    spdlog_logger_log_ffl(name, spdlog_error, __FUNCTION__, __FILE__, __LINE__, errcode, message)

//-----------------------------------------------------------------------------
// critical logging
#define LOG_CRITI(name, errcode, message) \
    spdlog_logger_log_ffl(name, spdlog_criti, __FUNCTION__, __FILE__, __LINE__, errcode, message)

//-----------------------------------------------------------------------------
// error logging with break
#define IF_ERROR_BREAK(name, errcode, message) { \
    if (errcode != LOG_SUCCESS) { \
        LOG_ERROR(name, errcode, message); \
        break; \
    } \
}

//-----------------------------------------------------------------------------
// error logging with continue
#define IF_ERROR_CONTINUE(name, errcode, message) { \
    if (errcode != LOG_SUCCESS) { \
        LOG_ERROR(name, errcode, message); \
        continue; \
    } \
}

//-----------------------------------------------------------------------------
// error logging with return
#define IF_ERROR_RETURN(name, errcode, message) { \
    if (errcode != LOG_SUCCESS) { \
        LOG_ERROR(name, errcode, message); \
        return errcode; \
    } \
}

//-----------------------------------------------------------------------------
// error logging with go on
#define IF_ERROR_GO_ON(name, errcode, message) { \
    if (errcode != LOG_SUCCESS) { \
        LOG_ERROR(name, errcode, message); \
    } \
}

//-----------------------------------------------------------------------------
// error logging method with break
#define IF_METHOD_ERROR_BREAK(name, errcode, method) { \
    errcode = method; \
    if (errcode != LOG_SUCCESS) { \
        LOG_ERROR(name, errcode, METHOD_ERROR #method); \
        break; \
    } \
}

//-----------------------------------------------------------------------------
// error logging method with continue
#define IF_METHOD_ERROR_CONTINUE(name, errcode, method) { \
    errcode = method; \
    if (errcode != LOG_SUCCESS) { \
        LOG_ERROR(name, errcode, METHOD_ERROR #method); \
        continue; \
    } \
}

//-----------------------------------------------------------------------------
// error logging method with return
#define IF_METHOD_ERROR_RETURN(name, errcode, method) { \
    errcode = method; \
    if (errcode != LOG_SUCCESS) { \
        LOG_ERROR(name, errcode, METHOD_ERROR #method); \
        return errcode; \
    } \
}

//-----------------------------------------------------------------------------
// error logging method with go on
#define IF_METHOD_ERROR_GO_ON(name, errcode, method) { \
    errcode = method; \
    if (errcode != LOG_SUCCESS) { \
        LOG_ERROR(name, errcode, METHOD_ERROR #method); \
    } \
}

//-----------------------------------------------------------------------------
// trace logging variadic
#define LOG_TRACE_VAR(name, message, ...) \
    spdlog_logger_log_ffl_var(name, spdlog_trace, __FUNCTION__, __FILE__, __LINE__, LOG_SUCCESS, message, __VA_ARGS__)

//-----------------------------------------------------------------------------
// debug logging
#define LOG_DEBUG_VAR(name, message, ...) \
    spdlog_logger_log_ffl_var(name, spdlog_debug, __FUNCTION__, __FILE__, __LINE__, LOG_SUCCESS, message, __VA_ARGS__)

//-----------------------------------------------------------------------------
// info logging
#define LOG_INFO_VAR(name, message, ...) \
    spdlog_logger_log_ffl_var(name, spdlog_info, __FUNCTION__, __FILE__, __LINE__, LOG_SUCCESS, message, __VA_ARGS__)

//-----------------------------------------------------------------------------
// warn logging
#define LOG_WARN_VAR(name, message, ...) \
    spdlog_logger_log_ffl_var(name, spdlog_warn, __FUNCTION__, __FILE__, __LINE__, LOG_SUCCESS, message, __VA_ARGS__)

//-----------------------------------------------------------------------------
// error logging
#define LOG_ERROR_VAR(name, errcode, message, ...) \
    spdlog_logger_log_ffl_var(name, spdlog_error, __FUNCTION__, __FILE__, __LINE__, errcode, message, __VA_ARGS__)

//-----------------------------------------------------------------------------
// critical logging
#define LOG_CRITI_VAR(name, errcode, message, ...) \
    spdlog_logger_log_ffl_var(name, spdlog_criti, __FUNCTION__, __FILE__, __LINE__, errcode, message, __VA_ARGS__)

//-----------------------------------------------------------------------------
// error logging with break
#define IF_ERROR_BREAK_VAR(name, errcode, message, ...) { \
    if (errcode != LOG_SUCCESS) { \
        LOG_ERROR_VAR(name, errcode, message, __VA_ARGS__); \
        break; \
    } \
}

//-----------------------------------------------------------------------------
// error logging with continue
#define IF_ERROR_CONTINUE_VAR(name, errcode, message, ...) { \
    if (errcode != LOG_SUCCESS) { \
        LOG_ERROR_VAR(name, errcode, message, __VA_ARGS__); \
        continue; \
    } \
}

//-----------------------------------------------------------------------------
// error logging with return
#define IF_ERROR_RETURN_VAR(name, errcode, message, ...) { \
    if (errcode != LOG_SUCCESS) { \
        LOG_ERROR_VAR(name, errcode, message, __VA_ARGS__); \
        return errcode; \
    } \
}

//-----------------------------------------------------------------------------
// error logging with go on
#define IF_ERROR_GO_ON_VAR(name, errcode, message, ...) { \
    if (errcode != LOG_SUCCESS) { \
        LOG_ERROR_VAR(name, errcode, message, __VA_ARGS__); \
    } \
}

//-----------------------------------------------------------------------------
#endif // __LOGGING_H_
