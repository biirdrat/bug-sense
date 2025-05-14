#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>

class Logger : public QObject
{
    Q_OBJECT

public:
    static Logger& getInstance();  // Singleton accessor

    void log(const QString& message);  // Log method

signals:
    void logMessageSignal(const QString& message);

private:
    explicit Logger(QObject *parent = nullptr);
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};

#endif // LOGGER_H