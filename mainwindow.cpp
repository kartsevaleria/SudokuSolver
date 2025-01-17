#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new sudokuTableModel;
    ui->sudokuTableView->setModel(model);
    initTable();
}

void MainWindow::initTable()
{
    int sectionSize = 31;
    int cntColumn = model->columnCount(QModelIndex());

    //Установка размера ячейки
    ui->sudokuTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->sudokuTableView->verticalHeader()->setDefaultSectionSize(sectionSize);
    for(int i = 0; i < cntColumn; ++i)
        ui->sudokuTableView->setColumnWidth(i,sectionSize);

    ui->sudokuTableView->setEditTriggers(QTableView::AllEditTriggers);

    ui->sudokuTableView->setStyleSheet("QHeaderView::section { background-color:red }");
}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::on_to_solve_clicked()
{
    //Заблокировать изменение таблицы
    model->isEditable(0);
}


void MainWindow::on_to_clear_clicked()
{
    //Разблокировать изменение таблицы
    model->isEditable(1);
}

