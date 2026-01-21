#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QSettings>
#include "worker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void chooseFolder();
    void startOrganizing();
    void togglePause();
    void toggleTheme();

private:
    Ui::MainWindow *ui;
    Worker *worker;
    QThread *thread;
    QSettings settings;
    bool darkMode;
};

#endif
