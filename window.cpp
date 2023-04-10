#include "window.h"

#include <QtDebug>
#include <QMouseEvent>
#include "label.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    setGeometry(500,400,300,200);

    _label = new Label{this};
}

bool Window::event(QEvent *e)
{
    if(e->type() == QEvent::MouseMove){
        qDebug() << "move in" << "Window::event.";
        e->accept();
    }
    return QWidget::event(e);
}

//void Window::mouseMoveEvent(QMouseEvent *event)
//{
//    qDebug() << "move in" << "Window::mouseMoveEvent.";
//}

Window::~Window()
{
}

