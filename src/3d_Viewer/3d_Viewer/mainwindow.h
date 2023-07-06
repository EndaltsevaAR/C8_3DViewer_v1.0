#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>

#include "gl_viewer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  gl_viewer *view;
  ~MainWindow();

 private slots:
  void on_button_pick_file_clicked();
  void do_move();
  void do_scale_bigger();
  void do_scale_smaller();
  void do_rotate();
  void set_color_edge();
  void set_color_vertex();
  void set_color_background();
  void do_extra_figure_changes();
  void do_reset_figure_changes();
  void do_extra_system_changes();
  void do_reset_system_changes();

 private:
  Ui::MainWindow *ui;

  double x_move_in, y_move_in, z_move_in;
  double x_rotate_in, y_rotate_in, z_rotate_in;
  double scale_bigger, scale_smaller;

  void set_start_information();
  void set_default_settings_figure();
  void set_default_settings_system();
  void set_start_affin();

  void save_settings();
  void load_settings();
};
#endif  // MAINWINDOW_H
