#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    char splitSymbol;

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int clearDatatable();

private slots:
    int importData();
};

#endif // MAINWINDOW_H
