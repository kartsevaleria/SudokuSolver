#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new sudokuTableModel;
    customItem = new customItemDelegate;
    customItem->setSourceModel(model);
    ui->sudokuTableView->setModel(customItem);
    model->setElemForDebug();
    solver = new Solver(model->columnCount(QModelIndex()));
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

    //ui->sudokuTableView->setStyleSheet("QHeaderView::section { background-color:red }");

}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::on_to_solve_clicked()
{
    //Заблокировать изменение таблицы
    model->isEditable(0);
    solver->setMatrix(model);

    if(solver->solve())
    {
        for(int i = 0; i < model->columnCount(QModelIndex()); i++)
        {
            for(int j = 0; j < model->rowCount(QModelIndex()); j++)
            {
                QVariant elem = model->data(model->index(i, j, QModelIndex()), Qt::EditRole);
                if(elem.toInt() == 0)
                {
                    model->setData(model->index(i, j, QModelIndex()), QVariant(solver->getNumber(i, j)), Qt::EditRole);
                }


            }
        }
    }
    else
        qDebug() << "Ошибка";

    qDebug() << "end all";
}


void MainWindow::on_to_clear_clicked()
{
    //Разблокировать изменение таблицы
    model->isEditable(1);
    model->clear();
    model->submit();
}

