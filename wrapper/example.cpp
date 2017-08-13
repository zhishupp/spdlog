#include "logging.h"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

//-----------------------------------------------------------------------------
void worker()
{
    TRACE_FUNCTION("console");

    for (int i = 0; i < 2; i++)
    {
        LOG_DEBUG("console", "thread running");
        LOG_INFO("console", "thread running");
        LOG_WARN("console", "thread running");
        LOG_ERROR("console", i, "thread running");
        LOG_CRITI("console", i, "thread running");

        LOG_DEBUG_VAR("console", "thread running: %d", i);
        LOG_INFO_VAR("console", "thread running: %d", i);
        LOG_WARN_VAR("console", "thread running: %d", i);
        LOG_ERROR_VAR("console", i, "thread running: %d", i);
        LOG_CRITI_VAR("console", i, "thread running: %d", i);
    }
}

//-----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    spdlog_set_level(spdlog_trace);
    spdlog_set_pattern("[%Y-%m-%d %H:%M:%S.%e][%L][%t] %v");
    spdlog_stdout_color_mt("console");

    LOG_INFO("console", "main thread start");

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

    LOG_INFO("console", "main thread end");

    spdlog_drop_all();

    return 0;
}
