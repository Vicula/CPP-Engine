// -*- lsst-c++ -*-
/**
 ******************************************************************************
 * @file: Logger.h
 * @brief: Class used for logging events to the console
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 Cattail Digital, LLC
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <vector>
#include <string>

enum LogType {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
};

struct LogEntry {
    LogType type;
    std::string message;
};

class Logger
{
public:
    static std::vector<LogEntry> messages;
    static void Log(const std::string& message);
    static void Err(const std::string& message);
};

#endif /* __LOGGER_H__ */