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
    load_settings();

    connect(ui->button_move, SIGNAL(clicked()), this, SLOT(do_move()));
    connect(ui->button_scale_bigger, SIGNAL(clicked()), this, SLOT(do_scale_bigger()));
    connect(ui->button_scale_smaller, SIGNAL(clicked()), this, SLOT(do_scale_smaller()));
    connect(ui->button_rotate, SIGNAL(clicked()), this, SLOT(do_rotate()));
    connect(ui->button_edge_color, SIGNAL(clicked()), this, SLOT(set_color_edge()));
    connect(ui->button_vertex_color, SIGNAL(clicked()), this, SLOT(set_color_vertex()));
    connect(ui->button_background_color, SIGNAL(clicked()), this, SLOT(set_color_background()));
    connect(ui->button_do_extra_figure, SIGNAL(clicked()), this, SLOT(do_extra_figure_changes()));
    connect(ui->button_reset_extra_figure, SIGNAL(clicked()), this, SLOT(do_reset_figure_changes()));
    connect(ui->button_do_extra_system, SIGNAL(clicked()), this, SLOT(do_extra_system_changes()));
    connect(ui->button_reset_extra_system, SIGNAL(clicked()), this, SLOT(do_reset_system_changes()));
}

MainWindow::~MainWindow()
{
    ui->viewer_gl_widget->destroy_viewer();
    save_settings();
    delete ui;
}

void MainWindow::set_start_affin() {
    x_move_in = 0, y_move_in = 0, z_move_in = 0;
    x_rotate_in = 0, y_rotate_in = 0, z_rotate_in = 0;
    scale_bigger = 1, scale_smaller = 1;

    ui->line_move_x->setText("");
    ui->line_move_y->setText("");
    ui->line_move_z->setText("");
    ui->line_rotate_x->setText("");
    ui->line_rotate_y->setText("");
    ui->line_rotate_z->setText("");
    ui->line_scale_bigger->setText("");
    ui->line_scale_smaller->setText("");
}

void MainWindow::set_default_settings_figure() {
    ui->radio_vertex_nothing->setChecked(true);
    ui->viewer_gl_widget->vert_type = NOTHING;

    ui->viewer_gl_widget->vertex_depth = DEPTH;
    ui->viewer_gl_widget->edge_depth = DEPTH;

    ui->viewer_gl_widget->edge_color = Qt::white;
     ui->viewer_gl_widget->vertex_color = Qt::black;
}

void MainWindow::set_default_settings_system() {
    set_start_affin();

    ui->radio_projection_parallel->setChecked(true);
    ui->viewer_gl_widget->is_projection_ortho = true;

    ui->radio_edge_solid->setChecked(true);
    ui->viewer_gl_widget->is_edge_solid = true;

    ui->viewer_gl_widget->background_color = Qt::yellow;
}


void MainWindow::set_start_information() {
    set_default_settings_figure();
    set_default_settings_system();
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
    QString filename_outside = QFileDialog::getOpenFileName(this, "Choooose", "./models/", "Object files (*.obj)");
    QByteArray file_name_bytes = filename_outside.toUtf8();
    const char* file_name_cstr = file_name_bytes.constData();

    ui->viewer_gl_widget->filename = filename_outside;

    if (start(file_name_cstr, &ui->viewer_gl_widget->total_data) == 1) {
        ui->viewer_gl_widget->is_file_loaded = true;
        QStringList parts = filename_outside.split("/");
        QString lastBit = parts.at(parts.size() - 1);
        ui->label_name_output->setText(lastBit);
        ui->label_vertex_num_output->setText(QString::number(ui->viewer_gl_widget->total_data.number_vertex));
        ui->label_edge_num_output->setText(QString::number(ui->viewer_gl_widget->total_data.number_polygons));
        set_start_affin();
        ui->viewer_gl_widget->update();
    } else {
        QMessageBox::warning(this, tr("Save Error"), tr("Некорректный файл"));
    }

}

void MainWindow::do_move() {
    if (ui->viewer_gl_widget->is_file_loaded) {
        x_move_in = ui->line_move_x->text().toDouble();
        y_move_in = ui->line_move_y->text().toDouble();
        z_move_in = ui->line_move_z->text().toDouble();
        move_coordinate(&ui->viewer_gl_widget->total_data.coordMatrix, x_move_in, y_move_in, z_move_in);
        ui->viewer_gl_widget->update();
    }
}

void MainWindow::do_scale_bigger() {
    if (ui->viewer_gl_widget->is_file_loaded) {
        scale_bigger = ui->line_scale_bigger->text().toDouble();
        if(scale_bigger != 0) {
            scale_coordinate(&ui->viewer_gl_widget->total_data.coordMatrix, scale_bigger);
            ui->viewer_gl_widget->update();

            scale_smaller = 1; // чтобы одновременно не было коеффициента и в увеличителе и в уменьшителе
            ui->line_scale_smaller->setText("");
        } else {
            QMessageBox::warning(this, tr("Scale Error"), tr("Не масштабируй в ноль, ведь бедную фигуру поглотят черные дыыыыры"));
            ui->line_scale_bigger->setText("");
            update();
        }
    }
}

void MainWindow::do_scale_smaller() {
    if (ui->viewer_gl_widget->is_file_loaded) {
        double coefficient_from_user = ui->line_scale_smaller->text().toDouble();
        if (coefficient_from_user != 0) {
            scale_smaller = 1/coefficient_from_user;
            scale_coordinate(&ui->viewer_gl_widget->total_data.coordMatrix, scale_smaller);
            ui->viewer_gl_widget->update();

            scale_bigger = 0; // чтобы одновременно не было коеффициента и в увеличителе и в уменьшителе
            ui->line_scale_bigger->setText("");
        } else {
            QMessageBox::warning(this, tr("Scale Error"), tr("Не масштабируй в ноль, ведь бедную фигуру поглотят черные дыыыыры"));
            ui->line_scale_smaller->setText("");
            update();
        }
    }
}

void MainWindow::do_rotate(){
    if (ui->viewer_gl_widget->is_file_loaded) {
        x_rotate_in = ui->line_rotate_x->text().toDouble();
        y_rotate_in = ui->line_rotate_y->text().toDouble();
        z_rotate_in = ui->line_rotate_z->text().toDouble();
        rotate_X(&ui->viewer_gl_widget->total_data.coordMatrix, x_rotate_in);
        rotate_Y(&ui->viewer_gl_widget->total_data.coordMatrix, y_rotate_in);
        rotate_Z(&ui->viewer_gl_widget->total_data.coordMatrix, z_rotate_in);
        ui->viewer_gl_widget->update();
    }
}

void MainWindow::set_color_edge() {
    QColor edge_color = QColorDialog::getColor(Qt::white, this, "Выберите цвет отображения ребер");
    if (edge_color.isValid() && edge_color != ui->viewer_gl_widget->background_color) {
      ui->viewer_gl_widget->edge_color = edge_color;
    }

}

void MainWindow::set_color_vertex(){
    QColor vertex_color = QColorDialog::getColor(Qt::white, this, "Выберите цвет отображения вершин");
    if (vertex_color.isValid() && vertex_color != ui->viewer_gl_widget->background_color) {
      ui->viewer_gl_widget->vertex_color = vertex_color;
    }

}

void MainWindow::set_color_background(){
    QColor background_color = QColorDialog::getColor(Qt::white, this, "Выберите цвет отображения вершин");
    if (background_color.isValid() && background_color != ui->viewer_gl_widget->edge_color) {
      ui->viewer_gl_widget->background_color = background_color;
    }
}

void MainWindow::do_extra_figure_changes(){
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

    ui->viewer_gl_widget->update();
}


void MainWindow:: do_reset_figure_changes() {
    set_default_settings_figure();
    ui->viewer_gl_widget->update();
}

void MainWindow:: do_extra_system_changes() {
    // обработка проекции
    if(ui->radio_projection_central->isChecked()) {
        ui->viewer_gl_widget->is_projection_ortho = false;
    } else {
        ui->viewer_gl_widget->is_projection_ortho = true;
    }
    ui->viewer_gl_widget->update();
}

void MainWindow:: do_reset_system_changes() {

    set_default_settings_system();
    ui->viewer_gl_widget->update();
}
