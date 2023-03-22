#include <QtGui>
#include "gotocelldialog.h"

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GoToCellDialog)
{
    ui->setupUi(this);

    //QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
    //lineEdit->setValidator(new QRegExpValidator(regExp, this));

    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void GoToCellDialog::on_lineEdit_textChanged() {
    ui->okButton->setEnabled(ui->lineEdit->hasAcceptableInput());
}

