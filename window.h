#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QEvent>

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();
public slots:
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    QLabel *_label;
    QPushButton *_button;
};
#endif // WINDOW_H
