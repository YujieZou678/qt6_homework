#include "sortdialog.h"
#include <QtWidgets>
#include <QtGui>
//
SortDialog::SortDialog(QWidget *parent)
    : QDialog(parent)
{
    ui = new Ui::SortDialog;
    ui->setupUi(this);

    ui->SecondaryGroupBox->hide();
    ui->TertiaryGroupBox->hide();
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    setColumnRange('A', 'Z');
}

void SortDialog::setColumnRange(QChar first, QChar last)
{
    ui->PrimaryColumnCombo->clear();
    ui->SecondaryColumnCombo->clear();
    ui->TertiaryColumnCombo->clear();

    ui->SecondaryColumnCombo->addItem(tr("Node"));
    ui->TertiaryColumnCombo->addItem(tr("Node"));
    ui->PrimaryColumnCombo->setMinimumSize(
        ui->SecondaryColumnCombo->sizeHint());
    //
    QChar ch = first;
    while( ch <= last){
        ui->PrimaryColumnCombo->addItem(QString(ch));
        ui->SecondaryColumnCombo->addItem(QString(ch));
        ui->TertiaryColumnCombo->addItem(QString(ch));
        ch = QChar(ch.unicode() + 1);
    }

}
