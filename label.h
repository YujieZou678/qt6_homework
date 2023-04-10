#ifndef LABEL_H
#define LABEL_H

#include <QLabel>
#include "button.h"

class Label : public QLabel
{
public:
    Label(QWidget *parent = nullptr);

//    virtual void mouseMoveEvent(QMouseEvent *) override;
    virtual bool event(QEvent *e)override;
private:
    Button *_button;
};

#endif // LABEL_H
