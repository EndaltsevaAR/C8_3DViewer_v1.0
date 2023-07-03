#include "mainwindow.h"
#include "ui_mainwindow.h"

int start(const char *file_name, obj_data *total_data);
int move_coordinate(coord_matrix *coordMatrix, double diffX, double diffY,
                    double diffZ);
int scale_coordinate(coord_matrix *coordMatrix, double diffX, double diffY,
                     double diffZ);
int rotate_X(coord_matrix *coordMatrix, double angleX);
int rotate_Y(coord_matrix *coordMatrix, double angleY);
int rotate_Z(coord_matrix *coordMatrix, double angleZ);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    set_start_information();
//    load_settings();

    connect(ui->button_move, SIGNAL(clicked()), this, SLOT(do_move()));
    connect(ui->button_move, SIGNAL(clicked()), this, SLOT(do_scale()));
    connect(ui->button_move, SIGNAL(clicked()), this, SLOT(do_rotate()));
    connect(ui->button_move, SIGNAL(clicked()), this, SLOT(set_color_edge()));
    connect(ui->button_move, SIGNAL(clicked()), this, SLOT(set_color_vertex()));
    connect(ui->button_move, SIGNAL(clicked()), this, SLOT(do_extra_changes()));


}

MainWindow::~MainWindow()
{
    ui->viewer_gl_widget->destroy_viewer();
 //   save_settings();
    delete ui;
}

void MainWindow::set_start_information() {
    x_move_in = 0, y_move_in = 0, z_move_in = 0;
    x_rotate_in = 0, y_rotate_in = 0, z_rotate_in = 0;
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

void MainWindow::do_move() {
    x_move_in = ui->line_move_x->text().toDouble();
    y_move_in = ui->line_move_y->text().toDouble();
    z_move_in = ui->line_move_z->text().toDouble();
    move_coordinate(&ui->viewer_gl_widget->total_data.coordMatrix, x_move_in, y_move_in, z_move_in);
    ui->viewer_gl_widget->update();
}

void MainWindow::do_scale() {
    x_scale_in = ui->line_scale_x->text().toDouble();
    y_scale_in = ui->line_scale_y->text().toDouble();
    z_scale_in = ui->line_scale_z->text().toDouble();
    scale_coordinate(&ui->viewer_gl_widget->total_data.coordMatrix, x_scale_in, y_scale_in, z_scale_in);
    ui->viewer_gl_widget->update();
}

void MainWindow::do_rotate(){
    x_rotate_in = ui->line_rotate_x->text().toDouble();
    y_rotate_in = ui->line_rotate_y->text().toDouble();
    z_rotate_in = ui->line_rotate_z->text().toDouble();
    rotate_X(&ui->viewer_gl_widget->total_data.coordMatrix, x_rotate_in);
    rotate_Y(&ui->viewer_gl_widget->total_data.coordMatrix, y_rotate_in);
    rotate_Z(&ui->viewer_gl_widget->total_data.coordMatrix, z_rotate_in);
    ui->viewer_gl_widget->update();
}

void MainWindow::set_color_edge() {

}

void MainWindow::set_color_vertex(){

}

void MainWindow::do_extra_changes(){
    // обработка проекции
    if(ui->radio_projection_central->isChecked()) {
        ui->viewer_gl_widget->is_projection_ortho = false;
    } else {
        ui->viewer_gl_widget->is_projection_ortho = true;
    }

    // обработка ребер
    if (ui->radio_edge_solid->isChecked()) {
        ui->viewer_gl_widget->is_edge_solid = true;
    } else {
        ui->viewer_gl_widget->is_edge_solid = false;
    }
    ui->viewer_gl_widget->edge_depth = ui->line_edge_depth->text().toDouble();

    // обработка вершин
    if (ui->radio_vertex_circle->isChecked()) {
        ui->viewer_gl_widget->vert_type = CIRLCE;
    } else if (ui->radio_vertex_square->isChecked()) {
        ui->viewer_gl_widget->vert_type = SQUARE;
    } else {
        ui->viewer_gl_widget->vert_type = NOTHING;
    }
    ui->viewer_gl_widget->vertex_depth = ui->line_vertex_depth->text().toDouble();

    // обработка смены цветов будут обработаны отдельно в соответствующих функциях

    ui->viewer_gl_widget->update();
}
