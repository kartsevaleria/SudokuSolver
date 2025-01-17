#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHeaderView>
#include <QAbstractItemView>
#include "sudokutablemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_to_solve_clicked();

    void on_to_clear_clicked();


private:
    Ui::MainWindow *ui;
    sudokuTableModel* model;

    void initTable();
};
#endif // MAINWINDOW_H
