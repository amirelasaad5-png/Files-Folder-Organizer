#include "worker.h"
#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <QThread>

Worker::Worker(const QString &path)
    : folderPath(path), paused(false), stopped(false) {}

void Worker::stop() {
    paused = true;
}

void Worker::resume() {
    paused = false;
}

void Worker::process()
{
    QDir dir(folderPath);
    QFileInfoList files = dir.entryInfoList(QDir::Files);

    QMap<QString, QString> types = {
        {"jpg","Images"}, {"png","Images"}, {"jpeg","Images"},
        {"mp4","Videos"}, {"mp3","Music"},
        {"pdf","Documents"}, {"zip","Archives"}
    };

    int total = files.size();
    int count = 0;

    for (const QFileInfo &file : files) {
        while (paused)
            QThread::msleep(200);

        QString ext = file.suffix().toLower();
        QString folder = types.value(ext, "Other");

        QDir target(folderPath + "/" + folder);
        if (!target.exists())
            dir.mkdir(folder);

        QString targetPath = target.absoluteFilePath(file.fileName());

        if (!QFile::exists(targetPath))
            QFile::rename(file.absoluteFilePath(), targetPath);

        count++;
        emit progress((count * 100) / total);
    }

    emit status("✔ اكتمل التنظيم");
    emit finished();
}
