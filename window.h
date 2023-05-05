// 文本编辑器
// author:zouyujie
// date: 2023-04-22

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QFileDialog>

class QTextEdit;
class QListWidget;
class QFont;
class QColor;
class QTextCharFormat;
class QListWidgetItem;
class QTimer;
class QLabel;

namespace Ui {
class window_bridge;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

    bool eventFilter(QObject *watched, QEvent *event) override;
    void update();

private:
    Ui::window_bridge *_ui;

    QString m_fileName;
    QTextEdit *textEdit;
    //QTextEdit *textEdit;
    //QListWidget *textList;
    QFont font;
    QColor color;
    QListWidgetItem *item;
    QListWidget *textList;
    QTimer *timer;
    QLabel *statusLabel_pos;
    QLabel *statusLabel_time;

private slots:
    void on_action_New_triggered();

    void on_action_Open_triggered();

    void on_action_Save_triggered();

    void on_actionSave_As_triggered();

    void on_actionE_xit_triggered();

    void on_actionCu_t_triggered();
    void on_action_copy_triggered();
    void on_action_Paste_triggered();
    void on_action_About_triggered();
    void on_action_Typeface_triggered();
    void on_action_Color_triggered();
    void on_action_Right_triggered();
    void on_action_Center_triggered();
    void on_action_Left_triggered();
    void on_action_Bold_triggered();
    void on_action_Italic_triggered();
    void on_action_UnderLine_triggered();
    void on_action_Undo_triggered();
    void on_action_Redo_triggered();
    void on_action_White_2_triggered();
    void on_action_LightYellow_triggered();
    void on_action_eeeddd_triggered();
    void on_action_f5f5f5_triggered();
    void on_dockWidget_allowedAreasChanged(const Qt::DockWidgetAreas &allowedAreas);
};

#endif // WINDOW_H
