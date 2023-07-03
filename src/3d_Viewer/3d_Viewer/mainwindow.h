#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>
#include <QVBoxLayout>
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

private slots:
    void on_button_pick_file_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
