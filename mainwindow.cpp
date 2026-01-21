#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    worker(nullptr),
    thread(nullptr),
    settings("MyCompany","Organizer"),
    darkMode(false)
{
    ui->setupUi(this);

    ui->linePath->setText(settings.value("lastPath").toString());

    connect(ui->btnBrowse, &QPushButton::clicked, this, &MainWindow::chooseFolder);
    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::startOrganizing);
    connect(ui->btnPause, &QPushButton::clicked, this, &MainWindow::togglePause);
    connect(ui->btnTheme, &QPushButton::clicked, this, &MainWindow::toggleTheme);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chooseFolder()
{
    QString dir = QFileDialog::getExistingDirectory(this, "اختر مجلد");
    if (!dir.isEmpty()) {
        ui->linePath->setText(dir);
        settings.setValue("lastPath", dir);
    }
}

void MainWindow::startOrganizing()
{
    thread = new QThread;
    worker = new Worker(ui->linePath->text());

    worker->moveToThread(thread);

    connect(thread, &QThread::started, worker, &Worker::process);
    connect(worker, &Worker::progress, ui->progressBar, &QProgressBar::setValue);
    connect(worker, &Worker::status, ui->statusLabel, &QLabel::setText);
    connect(worker, &Worker::finished, thread, &QThread::quit);

    connect(thread, &QThread::finished, worker, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    thread->start();
}

void MainWindow::togglePause()
{
    static bool paused = false;
    paused = !paused;

    if (paused) {
        worker->stop();
        ui->btnPause->setText("استئناف");
    } else {
        worker->resume();
        ui->btnPause->setText("إيقاف مؤقت");
    }
}

void MainWindow::toggleTheme()
{
    darkMode = !darkMode;

    if (darkMode) {
        qApp->setStyleSheet(R"(
QWidget {
    background-color: #121212;
    color: #ffffff;
    font-family: Segoe UI;
    font-size: 10pt;
}
QPushButton {
    background-color: #1f1f1f;
    border: 1px solid #333;
    border-radius: 6px;
    padding: 8px;
}
QPushButton:hover {
    background-color: #2b2b2b;
}
QProgressBar {
    border: 1px solid #444;
    border-radius: 5px;
    text-align: center;
}
QProgressBar::chunk {
    background-color: #3daee9;
    border-radius: 5px;
}
)");

    } else {
        qApp->setStyleSheet("");
    }
}
