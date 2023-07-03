#include "mainwindow.h"
#include "ui_mainwindow.h"

int start(const char *file_name, obj_data *total_data);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    set_start_information();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_start_information() {
    x_move_in = 0, y_move_in = 0, z_move_in = 0;
    x_rotate_in = 0, y_rotate_in = 0, z_rotate_z = 0;
    x_scale_in = 0, y_scale_in = 0, z_scale_in = 0;

    ui->radio_projection_parallel->setChecked(true);
    ui->viewer_gl_widget->is_projection_ortho = false;

    ui->radio_edge_solid->setChecked(true);
    ui->viewer_gl_widget->is_edge_solid = true;

    ui->radio_vertex_nothing->setChecked(true);
    ui->viewer_gl_widget->vert_type = NOTHING;

    ui->viewer_gl_widget->vertex_depth = DEPTH;
    ui->viewer_gl_widget->edge_depth = DEPTH;

    ui->viewer_gl_widget->edge_color = Qt::white;
    ui->viewer_gl_widget->background_color = Qt::yellow;
    ui->viewer_gl_widget->vertex_color = Qt::black;
}


void MainWindow::on_button_pick_file_clicked()
{
    QString filename_outside = QFileDialog::getOpenFileName(this, "Выбирай!", "./models/", "(*.obj");
    QByteArray file_name_bytes = filename_outside.toUtf8();
    const char* file_name_cstr = file_name_bytes.constData();


    ui->viewer_gl_widget->filename = filename_outside;

    if (start(file_name_cstr, &ui->viewer_gl_widget->total_data) == 1) {

    } else {
        QMessageBox::warning(this, tr("Save Error"), tr("Некорректный файл"));
    }

}

