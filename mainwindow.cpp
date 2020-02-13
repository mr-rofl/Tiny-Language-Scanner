#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QDebug"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
//    string path= (ui->path_text->text()).toStdString();

//    Scanner s(path);

//    string out=s.traverse_command();
//    ui->out_text->appendPlainText(QString::fromStdString(out));
    QString t=ui->out_text->toPlainText();
    qDebug()<<t;


}
