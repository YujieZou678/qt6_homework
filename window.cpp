#include "window.h"
#include <QDebug>

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(400, 500, 300, 200);

    _label = new QLabel("label", this);
    _label->setBackgroundRole(QPalette::Highlight);
    _label->setAutoFillBackground(true);
    _label->resize(80, 200);

    _button = new QPushButton("按钮", _label);
    _button->resize(80, 60);

    installEventFilter(this);
    _label->installEventFilter(this);
    _button->installEventFilter(this);
}

Window::~Window()
{
}

bool Window::eventFilter(QObject *watched, QEvent *e) {
    if (this == watched) {
            if (e->type() == QEvent::MouseMove) {
                qDebug() << "move in" << "window::event";
                e->ignore();
                return true;
            }
        }

    if (_label == watched) {
        if (e->type() == QEvent::MouseMove) {
            qDebug() << "move in" << "label::event";
            e->ignore();
            return true;
        }
    }

    if (_button == watched) {
        if (e->type() == QEvent::MouseMove) {
            qDebug() << "move in" << "button::event";
            e->ignore();
            return true;
        }
    }

    return QWidget::eventFilter(watched, e);
}

