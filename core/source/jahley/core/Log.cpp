// This source file was auto-generated by ClassMate++
// Created: 18 Jul 2016 7:57:36 pm
// Copyright (c) 2016, HurleyWorks

#include "berserkpch.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>  // for OutputDebugStringA

#include "Log.h"

std::once_flag g_start_time_flag;
std::chrono::steady_clock::time_point g_start_time;

using namespace g3;

// microsecondsCounter
int64_t microsecondsCounter()
{
    std::call_once (g_start_time_flag, []()
                    { g_start_time = std::chrono::steady_clock::now(); });
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds> (now - g_start_time).count();
}

// logFormatFunction
std::string logFormatFunction (const g3::LogMessage& msg)
{
    std::string now = std::to_string ((double)microsecondsCounter() * .000001);
    std::string out;
    out.append (now + "\t" + msg.level() + " [" + msg.threadID() + " " + msg.file() + "->" + msg.function() + ":" + msg.line() + "]\t");
    // out.append (now + "\t" + msg.level() + " [" + msg.threadID() + " " + msg.file() +  ":" + msg.line() + "]\t");
    return out;
}

class StdSink
{
 public:
    StdSink() {}
    ~StdSink() {}

    void receiveLogMessages (LogMessageMover message)
    {
        std::string msg = message.get().toString (_log_details_func);
        std::cout << msg;
        std::stringstream ss;
        ss << msg;

        OutputDebugStringA (ss.str().c_str());
    }

    void overrideLogDetails (LogMessage::LogDetailsFunc func)
    {
        _log_details_func = func;
    }

    void overrideLogHeader (const std::string& change)
    {
        _header = change;
        std::cout << change;
    }

 private:
    LogMessage::LogDetailsFunc _log_details_func;
    std::string _header;

    StdSink& operator= (const StdSink&) = delete;
    StdSink (const StdSink& other) = delete;
};

// ctor
LogHandler::LogHandler (FatalErrorCallback crashCallback, PreCrashCallback precrashCallback) :
    worker (g3::LogWorker::createLogWorker())
{
    auto handle = worker->addSink (std::make_unique<StdSink>(), &StdSink::receiveLogMessages);

    // initialize the logger before it can receive LOG calls
    initializeLogging (worker.get());

    g3::setFatalPreLoggingHook (precrashCallback);

    auto changeFormatting = handle->call (&StdSink::overrideLogDetails, logFormatFunction);

    const std::string newHeader = "\t\tLOG format: [hh:mm:ss uuu* LEVEL THREAD_ID FILE->FUNCTION:LINE] message\n\t\t(uuu*: microseconds fractions of the seconds value)\n\n";
    auto changeHeader = handle->call (&StdSink::overrideLogHeader, newHeader);

    changeFormatting.wait();
    changeHeader.wait();

    g3::setFatalExitHandler (crashCallback);
    LOG (INFO) << "Logger initialized";
}