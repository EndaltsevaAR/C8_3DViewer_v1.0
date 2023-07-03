#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QVBoxLayout>
#include <QSettings>
#include "gl_viewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    gl_viewer *view;
    ~MainWindow();

    double x_move_in, y_move_in, z_move_in;
    double x_rotate_in, y_rotate_in, z_rotate_z;
    double x_scale_in, y_scale_in, z_scale_in;

   void set_start_information();
   void save_settings();
   void load_settings();

private slots:
    void on_button_pick_file_clicked();

private:
    Ui::MainWindow *ui;
    QSettings *settings;
};
#endif // MAINWINDOW_H
