#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QString>
#include <atomic>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(const QString &path);

signals:
    void progress(int value);
    void finished();
    void status(QString text);

public slots:
    void process();
    void stop();
    void resume();

private:
    QString folderPath;
    std::atomic<bool> paused;
    std::atomic<bool> stopped;
};

#endif // WORKER_H
