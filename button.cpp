#include "button.h"
#include <QDebug>
#include <QEvent>

Button::Button(QWidget *parent)
    : QPushButton(parent)
{
    setText("按钮");
}

bool Button::event(QEvent *e) {
    if (e->type() == QEvent::MouseMove) {
        qDebug() << "move in" << "Button::event";
        //e->accept();
        e->ignore();
        return true;
    }
    return QPushButton::event(e);
}
