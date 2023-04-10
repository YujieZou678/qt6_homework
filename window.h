#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
class Label;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    virtual bool event(QEvent *event) override;
//    virtual void mouseMoveEvent(QMouseEvent *event)override;
    ~Window();
private:
    Label *_label;
};
#endif // WINDOW_H
