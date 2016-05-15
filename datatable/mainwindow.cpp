#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageLogger>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->splitSymbol=',';

    ui->setupUi(this);

    ui->tableWidget->setSortingEnabled(true);

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(3);

    connect(ui->openButton,SIGNAL(released()),this,SLOT(importData()));
}

int MainWindow::importData(){
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "$HOME", ("csv File(*.csv)"));
    QString data;
    QFile importedCSV(fileName);
    QStringList rowOfData;
    QStringList rowData;

    QMessageLogger logger;

    rowOfData.clear();
    rowData.clear();
    this->clearDatatable();

    if (importedCSV.open(QFile::ReadOnly))
    {
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        importedCSV.close();
    }

    QByteArray ba;

    int rowSize=0,columnSize=0;
    rowSize = rowOfData.size();
    for (int x = 0; x < rowOfData.size(); x++)
    {
        rowData = rowOfData.at(x).split(this->splitSymbol);
        if(rowData.size() > columnSize){
            columnSize = rowData.size();
        }
    }

    ui->tableWidget->setColumnCount(columnSize);
    ui->tableWidget->setRowCount(rowSize);

    for (int x = 0; x < rowSize; x++)
    {
        rowData = rowOfData.at(x).split(this->splitSymbol);

//        ba = rowOfData[x].toLatin1();
//        logger.info(ba.data());

        for (int y = 0; y < columnSize; y++)
        {
//            ba = rowData[y].toLatin1();
//            logger.info(ba.data());
            QTableWidgetItem* textItem = new QTableWidgetItem;
            if(y<rowData.size()){
                textItem->setText(rowData[y]);
            }
            ui->tableWidget->setItem(x,y,textItem);
        }
    }

    ui->tableWidget->resizeRowsToContents();
    ui->tableWidget->resizeColumnsToContents();

    return 0;
}

int MainWindow::clearDatatable(){
    int rowSize    = ui->tableWidget->rowCount();
    int columnSize = ui->tableWidget->columnCount();
    for(int x=0;x<rowSize;x++){
        for(int y=0;y<columnSize;y++){
            QTableWidgetItem* textItem = ui->tableWidget->item(x,y);
            delete textItem;
        }
    }
    return 0;
}


MainWindow::~MainWindow()
{
    delete ui;
}
