#include "Logger.h"

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

Logger::Logger(QObject *parent) : QObject(parent)
{
}

void Logger::log(LogLevel log_level, const QString& message)
{
    QString timestamp = QDateTime::currentDateTime().toString("MM/dd/yyyy hh:mm:ss");
    QString formattedMessage = QString("%1 - %2").arg(timestamp, message);

    emit logMessageSignal(log_level, formattedMessage);
}