#include "window.h"
#include "./ui_window.h"

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QFileDialog>
#include <QEvent>
#include <QKeyEvent>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    resize(800 ,600);

    //初始化
    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    m_fileName = "";

    //处理
    setCentralWidget(videoWidget);
    player->setVideoOutput(videoWidget);

    installEventFilter(this);

    //播放状态检测
    connect(player, &QMediaPlayer::playbackStateChanged, [=](){
        switch (player->playbackState()) {
        case QMediaPlayer::PlayingState:
            qDebug() << "Playing";
            break;
        case QMediaPlayer::PausedState:
            qDebug() << "Paused";
            break;
        case QMediaPlayer::StoppedState:
            qDebug() << "Stopped";
            break;
        default:
            break;
        }
    });
}

Window::~Window()
{
    delete ui;
}

bool Window::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            if (this->isFullScreen()) {
                this->showNormal();
                ui->menubar->setHidden(false);
                ui->statusbar->setHidden(false);
                ui->toolbar->setHidden(false);
            } else {
                this->showFullScreen();
                ui->menubar->setHidden(true);
                ui->statusbar->setHidden(true);
                ui->toolbar->setHidden(true);
            }
            return true;
        }

        //全屏后按ESC，恢复
        QKeyEvent *e = static_cast<QKeyEvent*>(event);
        if (e->key() == Qt::Key_Escape) {
            if (this->isFullScreen()) {
                this->showNormal();
                ui->menubar->setHidden(false);
                ui->statusbar->setHidden(false);
                ui->toolbar->setHidden(false);
            }

            return true;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}


void Window::on_action_Open_triggered()
{
    //打开文件
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "*");
    if (fileName == "") return;
    else {
        //播放配置
        m_fileName = fileName;
        player->setSource(QUrl(m_fileName));
        //播放视频
        QAudioOutput *audio = new QAudioOutput(this);
        player->setAudioOutput(audio);
        player->play();

        ui->action_Pause->setEnabled(true);
        ui->action_Stop->setEnabled(true);
    }

}


void Window::on_action_Exit_triggered()
{
    QApplication::exit();
}


void Window::on_action_Close_triggered()
{
    m_fileName = "";

    ui->action_Start->setEnabled(false);
    ui->action_Pause->setEnabled(false);
    ui->action_Stop->setEnabled(false);

    player->stop();
}


void Window::on_actionFullScreen_triggered()
{
    this->showFullScreen();
    ui->menubar->setHidden(true);
    ui->statusbar->setHidden(true);
    ui->toolbar->setHidden(true);
}


void Window::on_action_Start_triggered()
{
    ui->action_Start->setEnabled(false);
    ui->action_Pause->setEnabled(true);
    ui->action_Stop->setEnabled(true);

    QAudioOutput *audio = new QAudioOutput(this);
    player->setAudioOutput(audio);
    player->play();
}


void Window::on_action_Pause_triggered()
{
    ui->action_Start->setEnabled(true);
    ui->action_Pause->setEnabled(false);
    ui->action_Stop->setEnabled(true);

    player->pause();
}


void Window::on_action_Stop_triggered()
{
    ui->action_Stop->setEnabled(false);
    ui->action_Pause->setEnabled(false);
    ui->action_Start->setEnabled(true);

    player->stop();
    //player->pause();

}




