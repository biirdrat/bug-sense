#include "Logger.h"

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

Logger::Logger(QObject *parent) : QObject(parent)
{
}

void Logger::log(const QString& message)
{
    emit logMessageSignal(message);
}