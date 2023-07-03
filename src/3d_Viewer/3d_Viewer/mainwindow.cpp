#include "mainwindow.h"
#include "ui_mainwindow.h"

int start(const char *file_name, obj_data *total_data);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    set_start_information();
    load_settings();

}

MainWindow::~MainWindow()
{
    ui->viewer_gl_widget->destroy_viewer();
    save_settings();
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

void MainWindow::save_settings() {
    settings->beginGroup("Common");
        settings->setValue("background_color", ui->viewer_gl_widget->background_color);
        settings->setValue("projection_type", ui->viewer_gl_widget->is_projection_ortho);
    settings->endGroup();

    settings->beginGroup("Vertex");
        settings->setValue("vertex_type", ui->viewer_gl_widget->vert_type);
        settings->setValue("vertex_color", ui->viewer_gl_widget->vertex_color);
        settings->setValue("vertex_depth", ui->viewer_gl_widget->vertex_depth);
    settings->endGroup();

    settings->beginGroup("Edge");
        settings->setValue("edge_type", ui->viewer_gl_widget->is_edge_solid);
        settings->setValue("edge_color", ui->viewer_gl_widget->edge_color);
        settings->setValue("edge_depth", ui->viewer_gl_widget->edge_depth);
    settings->endGroup();
}

void MainWindow::load_settings() {
    settings = new QSettings("3D", "Config");
    settings->beginGroup("Common");
         ui->viewer_gl_widget->background_color = settings->value("background_color").toString();
         ui->viewer_gl_widget->is_projection_ortho = settings->value("projection_type").toBool();
    settings->endGroup();

    settings->beginGroup("Vertex");
        if (settings->value("vertex_type") == CIRLCE) {
            ui->radio_vertex_circle->setChecked(true);
        } else if (settings->value("vertex_type") == SQUARE) {
            ui->radio_vertex_square->setChecked(true);
        } else if (settings->value("vertex_type") == NOTHING) {
            ui->radio_vertex_nothing->setChecked(true);
        }

        ui->viewer_gl_widget->vert_type = (enum vertex_type)settings->value("vertex_type").toInt();
        ui->viewer_gl_widget->vertex_color = settings->value("vertex_color").toString();
        ui->viewer_gl_widget->vertex_depth = settings->value("vertex_depth").toDouble();
        ui->line_vertex_depth->setText(settings->value("vertex_depth").toString());
    settings->endGroup();

    settings->beginGroup("Edge");
        if (settings->value("edge_type").toBool()) {
            ui->radio_edge_solid->setChecked(true);
        } else {
            ui->radio_edge_dotted->setChecked(true);
        }

    ui->viewer_gl_widget->is_edge_solid = settings->value("edge_type").toBool();
    ui->viewer_gl_widget->edge_color = settings->value("edge_color").toString();
    ui->viewer_gl_widget->edge_depth = settings->value("edge_depth").toDouble();
    ui->line_edge_depth->setText(settings->value("edge_depth").toString());

    settings->endGroup();


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

