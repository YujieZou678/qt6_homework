#include "window.h"

#include <QStatusBar>
#include <QScrollBar>
#include <QLabel>
#include <QTextEdit>
#include <QFont>
#include <QColor>
#include <QDockWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QTextCharFormat>
#include <QWheelEvent>
#include <QDesktopServices>
#include <QTimer>
#include <QTextStream>

#include <sstream>
using std::stringstream;

#include "ui_window.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::window_bridge)
{
    _ui->setupUi(this);

    //中心部件
    textEdit = new QTextEdit(this);
    QFont font;
    font.setPointSize(11);
    textEdit->setFont(font);
    textEdit->setText("I am TextEdit...");
    textEdit->setObjectName("TextEdit");
    //textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    textEdit->setStyleSheet("background-color: #eeeddd;");
    setCentralWidget(textEdit);

    //状态栏
    QStatusBar *status = new QStatusBar(this);
    status->setObjectName("StatusBar");
    setStatusBar(status);

    statusLabel_pos = new QLabel("",this);
    statusLabel_time = new QLabel("time", this);
    statusLabel_time->setStyleSheet("QLabel {\
                         background-color: #eeeddd;\
                         border-radius: 12%;\
                         font-weight: bold;\
                           }");
    //status->showMessage("Welcome!", 3000);  //左侧
    status->addWidget(statusLabel_pos);
    status->addPermanentWidget(statusLabel_time);  //右侧永久
    //铆接部件
    //QLabel *titleLabel = new QLabel("行数");
    //titleLabel->setAlignment(Qt::AlignCenter);
    QWidget *temp = new QWidget;
    _ui->dockWidget->setTitleBarWidget(temp);

    textList = new QListWidget(this);
    std::stringstream oss;
    oss << "font-size: " << textEdit->font().pointSize()+0.62125 << "pt;";
    textList->setStyleSheet(QString::fromStdString(oss.str()));
    //textList->setStyleSheet("font-size: 25pt;");
    for (int i = 1; i <= 100; i++) {
        item = new QListWidgetItem(QString("%1").arg(i));
        textList->addItem(item);
        item->setTextAlignment(Qt::AlignCenter);
    }
    textList->setFixedWidth(50);
    textList->setObjectName("文本列表");
    textList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _ui->dockWidget->setWidget(textList);
    //时间
    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout, this, &Window::update);
    QDateTime datetime = QDateTime::currentDateTime();
    statusLabel_time->setText(datetime.toString("t yyyy-MM-dd hh:mm:ss a dddd\t"));

    installEventFilter(this);
    textList->verticalScrollBar()->installEventFilter(this);
    textEdit->verticalScrollBar()->installEventFilter(this);
}

Window::~Window()
{
    delete _ui;
}

void Window::update() {
    QDateTime datetime = QDateTime::currentDateTime();
    statusLabel_time->setText(datetime.toString("t yyyy-MM-dd hh:mm:ss a dddd\t"));
}

bool Window::eventFilter(QObject *watched, QEvent *event) {
    QWheelEvent *e = static_cast<QWheelEvent*>(event);

    if (watched == textEdit->verticalScrollBar()) {
        textList->verticalScrollBar()->setSliderPosition(textEdit->verticalScrollBar()->sliderPosition() /17.141);

        if (e->modifiers() == Qt::ControlModifier) {
            if (event->type() == QEvent::Wheel) {
                if (e->angleDelta().ry() > 0) {
                    if (textEdit->font().pointSize() >= 25) return true;
                    textEdit->zoomIn();

                } else if (e->angleDelta().ry() < 0){
                    if (textEdit->font().pointSize() <= 6) return true;
                    textEdit->zoomOut();

                }
                stringstream oss;
                oss << "font-size: " << textEdit->font().pointSize() << "pt;";
                qDebug() << textEdit->font().pointSize();

                textList->setStyleSheet(QString::fromStdString(oss.str()));
                //textList->setStyleSheet("font-size: 20pt;");
                return true;
            }
        }
    }

    if (watched == textList->verticalScrollBar()) {
        return true;
    }

    if (watched == this) {
        if (event->type() == QEvent::Close) {
            QString fileName = statusLabel_pos->text();
            /*未打开文件的情况*/
            if (fileName == "") {
                if (textEdit->toPlainText() != "I am TextEdit...") {
                    if (QMessageBox::warning(this, "警告", "文件还未保存，确定退出？", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
event->accept();
                    } else{
event->ignore();
                    }
                }
            } else {
                /*打开文件的情况*/
                QFile file(fileName);
                if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) QMessageBox::warning(this, tr("错误"), tr("打开文件失败"));
                else {
                    if (!file.isReadable()) QMessageBox::warning(this, tr("错误"), tr("该文件不可读"));
                    else {
QTextStream textStream(&file);
if (textEdit->toPlainText() != textStream.readAll()) {
                    if (QMessageBox::warning(this, "警告", "文件还未保存，确定退出？", QMessageBox::Yes|QMessageBox::No) == QMessageBox::Yes) {
event->accept();
                    } else{
event->ignore();
                    }
}
                    }
                }
            }
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
}


void Window::on_action_New_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), tr(""), tr("Text File(*)"));
    if (fileName =="") return;
    else {
        QFile file(fileName);
        /*以下WriteOnly...即新建*/
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) QMessageBox::warning(this, tr("错误"), tr("创建文件失败"));
        else {
            /*打开新建文件*/
            file.close();  //先关闭
            if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) { QMessageBox::warning(this, tr("错误"), tr("打开文件失败")); }
            else {
                /*文件能打开*/
                if (!file.isReadable()) QMessageBox::warning(this, tr("错误"), tr("该文件不可读"));
                else {
                    /*文件可读*/
                    QTextStream textStream(&file);  //读取文件
                    //while (!textStream.atEnd()) textEdit->setPlainText(textStream.readAll());
                    textEdit->setPlainText(textStream.readAll());
                    statusLabel_pos->setText(fileName);
                    file.close();
                }
            }
        }
    }
}


void Window::on_action_Open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), tr(""), tr("Text File(*)"));
    if (fileName == "") return;
    else {
        /*文件名不为空*/
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) { QMessageBox::warning(this, tr("错误"), tr("打开文件失败")); }
        else {
            /*文件能打开*/
            if (!file.isReadable()) QMessageBox::warning(this, tr("错误"), tr("该文件不可读"));
            else {
                /*文件可读*/
                QTextStream textStream(&file);  //读取文件
                //while (!textStream.atEnd()) textEdit->setPlainText(textStream.readAll());
                textEdit->setPlainText(textStream.readAll());
                statusLabel_pos->setText(fileName);
                file.close();
            }
        }
    }

}


void Window::on_action_Save_triggered()
{
    QString fileName = statusLabel_pos->text();
    if (fileName == "") {
       /*未打开文件，此时保存相当于另存为*/
        fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text File(*)");
        if (fileName == "") return;
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) QMessageBox::warning(this, "错误", "创建文件失败");
        else {
            QTextStream textStream(&file);
            textStream << textEdit->toPlainText();
            QMessageBox::information(this, "保存文件", "保存成功", QMessageBox::Ok);
            file.close();
        }
    }
    //--------------------------------------
    else {
        /*有打开文件，保存到当前文件*/
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) QMessageBox::warning(this, "错误", "创建文件失败");
        else {
            QTextStream textStream(&file);
            textStream << textEdit->toPlainText();
            QMessageBox::information(this, "保存文件", "保存成功", QMessageBox::Ok);
            file.close();
        }
    }
}


void Window::on_actionSave_As_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Text File(*)");
    if (fileName == "") return;
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) QMessageBox::warning(this, "错误", "创建文件失败");
    else {
        QTextStream textStream(&file);
        textStream << textEdit->toPlainText();
        QMessageBox::information(this, "保存文件", "保存成功", QMessageBox::Ok);
        file.close();
    }
}


void Window::on_actionE_xit_triggered()
{
    QApplication::exit();
    //close();
}


void Window::on_actionCu_t_triggered()
{
    textEdit->cut();
}


void Window::on_action_copy_triggered()
{
    textEdit->copy();
}


void Window::on_action_Paste_triggered()
{
    textEdit->paste();
}


void Window::on_action_About_triggered()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("https://www.qt.io/zh-cn/")));
}


void Window::on_action_Typeface_triggered()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok, font, this, "选择文本框要设置的字体");

    if (ok) {
        font = f;
        textEdit->setCurrentFont(font);
    }
}


void Window::on_action_Color_triggered()
{
    QColor c = QColorDialog::getColor(color, this, "颜色选择框");
    if (c.isValid()) {
        color = c;
        textEdit->setTextColor(color);
    }
}


void Window::on_action_Right_triggered()
{
    textEdit->setAlignment(Qt::AlignRight);
}


void Window::on_action_Center_triggered()
{
    textEdit->setAlignment(Qt::AlignCenter);
}


void Window::on_action_Left_triggered()
{
    textEdit->setAlignment(Qt::AlignLeft);
}


void Window::on_action_Bold_triggered()
{
    QTextCharFormat fmt;
    if (textEdit->fontWeight() != QFont::Bold) {
        fmt.setFontWeight(QFont::Bold);
    } else fmt.setFontWeight(QFont::Normal);

    textEdit->mergeCurrentCharFormat(fmt);
}


void Window::on_action_Italic_triggered()
{
    QTextCharFormat fmt;
    if (!textEdit->fontItalic()) {
        fmt.setFontItalic(true);
    } else fmt.setFontItalic(false);

    textEdit->mergeCurrentCharFormat(fmt);
}


void Window::on_action_UnderLine_triggered()
{
    QTextCharFormat fmt;
    if (!textEdit->fontUnderline()) {
        fmt.setFontUnderline(true);
    } else fmt.setFontUnderline(false);

    textEdit->mergeCurrentCharFormat(fmt);
}


void Window::on_action_Undo_triggered()
{
    textEdit->undo();
}


void Window::on_action_Redo_triggered()
{
    textEdit->redo();
}


void Window::on_action_White_2_triggered()
{
    textEdit->setStyleSheet("background-color: white");
}


void Window::on_action_LightYellow_triggered()
{
    textEdit->setStyleSheet("background-color: lightyellow");
}


void Window::on_action_eeeddd_triggered()
{
    textEdit->setStyleSheet("background-color: #eeeddd;");
}


void Window::on_action_f5f5f5_triggered()
{
    textEdit->setStyleSheet("background-color: #f5f5f5;");
}


void Window::on_dockWidget_allowedAreasChanged(const Qt::DockWidgetAreas &allowedAreas)
{
    //_ui->dockWidget
}

