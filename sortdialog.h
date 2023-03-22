#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include "ui_sortdialog.h"

class SortDialog : public QDialog
{
    Q_OBJECT
public:
    SortDialog(QWidget* parent = 0);

    void setColumnRange(QChar first, QChar last);
private:
    Ui::SortDialog *ui;
};

#endif
