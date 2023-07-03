#include "mainwindow.h"
#include "ui_mainwindow.h"

int start(const char *file_name, obj_data *total_data);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_pick_file_clicked()
{
    QString filename_outside = QFileDialog::getOpenFileName(this, "Выбирай!", "./models/", "(*.obj");

    ui->viewer_gl_widget->filename = filename_outside;

    if (start(filename_outside, &ui->viewer_gl_widget->total_data)) {

    }


}

