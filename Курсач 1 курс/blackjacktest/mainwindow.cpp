#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewindow.h"
#include <QObject>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("WhiteJimmy");
    this->setStyleSheet(R"(
    QMainWindow {
        background-color: #222;
    }

    QLabel {
        color: white;
        font-size: 100px;
        font-weight: bold;
        qproperty-alignment: AlignCenter;
    }

    QPushButton {
        background-color: #444;
        color: white;
        padding: 8px;
        border-radius: 6px;
        font-weight: bold;
    }

    QPushButton:hover {
        background-color: #555;
    }

    QPushButton:disabled {
        background-color: #333;
        color: gray;
    }

    QLineEdit {
        background-color: #333;
        color: white;
        border: 1px solid #FF1493;
        border-radius: 4px;
        padding: 4px;
    }

    QComboBox {
        background-color: #333;
        color: white;
        border: 1px solid #FF1493;
        border-radius: 4px;
        padding: 4px;
    }

    QGroupBox {
        border: 2px solid #FF1493;
        border-radius: 8px;
        margin-top: 16px;
    }

    QGroupBox::title {
        color: #FF1493;
        subcontrol-origin: margin;
        left: 10px;
        padding: 0 3px 0 3px;
    }

    QFrame {
        border: none;
        background-color: transparent;
    }
)");
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::startGame);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame()
{
    GameWindow = new gameWindow();
    GameWindow->setAttribute(Qt::WA_DeleteOnClose);
    GameWindow->show();
    this->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    QApplication::quit();
}

