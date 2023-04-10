#include "label.h"
#include <QMouseEvent>

Label::Label(QWidget *parent):QLabel(parent)
{
    setText("event handing");
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);

    _button = new Button{this};
}

//void Label::mouseMoveEvent(QMouseEvent *event)
//{
//    //    move(event->scenePosition().toPoint());
//    qDebug() << "move in" << "Label::mouseMoveEvent.";
//}

bool Label::event(QEvent *e)
{
    if(e->type() == QEvent::MouseMove){
        qDebug() << "move in" << "Label::event.";
        //e->accept();
        e->ignore();
        return true;
    }
    return QWidget::event(e);
}
