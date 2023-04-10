#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class Button : QPushButton
{
    Q_OBJECT

public:
    Button(QWidget *parent = nullptr);


    virtual bool event(QEvent *e) override;
private:

};

#endif // BUTTON_H
