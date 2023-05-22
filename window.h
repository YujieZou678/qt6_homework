#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class QVideoWidget;
class QMediaPlayer;
class QAudioOutput;

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_action_Open_triggered();

    void on_action_Exit_triggered();

    void on_action_Close_triggered();

    void on_actionFullScreen_triggered();

    void on_action_Start_triggered();

    void on_action_Stop_triggered();

    void on_action_Pause_triggered();

private:
    Ui::Window *ui;

    QVideoWidget *videoWidget;
    QMediaPlayer *player;
    //QAudioOutput *audioOutput;  //要在每次播放(play)之前重新添加音频，不然可能会突然没声音，原因不知

    QString m_fileName;
};
#endif // WINDOW_H
