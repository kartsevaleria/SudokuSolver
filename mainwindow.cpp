#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new sudokuTableModel;
    customItem = new customItemDelegate;

    QObject::connect(this, SIGNAL(click_solve()), model, SLOT(pullNullMatrix()));
    QObject::connect(this, SIGNAL(click_clear()), model, SLOT(clearNullMatrix()));
    QObject::connect(customItem, SIGNAL(updateIsNull(const QModelIndex&, bool&)), model, SLOT(isNullElem(const QModelIndex&, bool&)));

    customItem->setSourceModel(model);
    ui->sudokuTableView->setModel(customItem);
    model->setElemForDebug();
    solver = new Solver(model->columnCount(QModelIndex()));

    initTable();
    initComboBox();
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

}

void MainWindow::initComboBox()
{
    ui->cb_algorithm->addItem("Обратного отслеживания");
    ui->cb_algorithm->addItem("Обратного отслеживания с сортировкой");
}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::on_to_solve_clicked()
{
    emit click_solve();
    //Заблокировать изменение таблицы
    model->isEditable(0);
    solver->setMatrix(model);
    qint64 timer;

    bool isSolve;
    try
    {
        isSolve = solver->solve(timer, ui->cb_algorithm->currentIndex());
    }
    catch (const char* what)
    {
        QErrorMessage error;
        error.showMessage(what);
        error.exec();
    }

    if(isSolve)
    {
        ui->calcTime->setText(QString::number(timer));
        for(int i = 0; i < model->columnCount(QModelIndex()); i++)
        {
            for(int j = 0; j < model->rowCount(QModelIndex()); j++)
            {
                QVariant elem = model->data(model->index(i, j, QModelIndex()), Qt::EditRole);
                if(elem.toInt() == 0)
                    model->setData(model->index(i, j, QModelIndex()), QVariant(solver->getNumber(i, j)), Qt::EditRole);
            }
        }
    }
    else
    {
        ui->calcTime->setText(" ");
        QErrorMessage error;
        error.showMessage("Нет решения");
        error.exec();
    }

}


void MainWindow::on_to_clear_clicked()
{
    //Разблокировать изменение таблицы
    emit click_clear();
    ui->calcTime->setText(" ");
    model->isEditable(1);
    model->clear();
}

