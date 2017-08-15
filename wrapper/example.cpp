#include "logging.h"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

//-----------------------------------------------------------------------------
int func(int errcode)
{
    return errcode;
}

//-----------------------------------------------------------------------------
int test_if_error()
{
    for (int i = 0; i < 2; ++i)
    {
        IF_ERROR_BREAK("console", i, "test_if_error");
    }

    for (int i = 0; i < 2; ++i)
    {
        IF_ERROR_CONTINUE("console", i, "test_if_error");
    }

    for (int i = 0; i < 2; ++i)
    {
        IF_ERROR_GO_ON("console", i, "test_if_error");
    }

    for (int i = 0; i < 2; ++i)
    {
        IF_ERROR_RETURN("console", i, "test_if_error");
    }

    return 0;
}

//-----------------------------------------------------------------------------
int test_if_method_error()
{
    int e = 0;

    for (int i = 0; i < 2; ++i)
    {
        IF_METHOD_ERROR_BREAK("console", e, func(i));
    }

    for (int i = 0; i < 2; ++i)
    {
        IF_METHOD_ERROR_CONTINUE("console", e, func(i));
    }

    for (int i = 0; i < 2; ++i)
    {
        IF_METHOD_ERROR_GO_ON("console", e, func(i));
    }

    for (int i = 0; i < 2; ++i)
    {
        IF_METHOD_ERROR_RETURN("console", e, func(i));
    }

    return 0;
}

//-----------------------------------------------------------------------------
void worker()
{
    TRACE_FUNCTION("console");

    for (int i = 0; i < 2; i++)
    {
        SPD_LOG_DEBUG("console", "thread running");
        SPD_LOG_INFO("console", "thread running");
        SPD_LOG_WARN("console", "thread running");
        SPD_LOG_ERROR("console", i, "thread running");
        SPD_LOG_CRITI("console", i, "thread running");

        SPD_LOG_DEBUG_VAR("console", "thread running: %d", i);
        SPD_LOG_INFO_VAR("console", "thread running: %d", i);
        SPD_LOG_WARN_VAR("console", "thread running: %d", i);
        SPD_LOG_ERROR_VAR("console", i, "thread running: %d", i);
        SPD_LOG_CRITI_VAR("console", i, "thread running: %d", i);
    }
}

//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    spdlog_set_level(spdlog_trace);
    spdlog_set_pattern("[%Y-%m-%d %H:%M:%S.%e][%L][%t] %v");
    spdlog_stdout_color_mt("console");

    SPD_LOG_INFO("console", "main thread start");

    //auto start = std::chrono::system_clock::now();

    std::vector<std::thread> vecThread;
    for (int i = 0; i < 2; ++i)
    {
        vecThread.emplace_back(worker);
    }

    for (size_t i = 0; i < vecThread.size(); ++i)
    {
        vecThread[i].join();
    }

    //auto end = std::chrono::system_clock::now();

    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    //std::cout << duration.count() << std::endl;

    test_if_error();
    test_if_method_error();

    SPD_LOG_INFO("console", "main thread end");

    spdlog_drop_all();

    return 0;
}
