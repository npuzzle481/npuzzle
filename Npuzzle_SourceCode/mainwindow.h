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
    ~MainWindow();

private slots:
    //void on_button_loadState_clicked();



    void on_button_generatePuzzle_clicked();


    void on_button_start_toggled(bool checked);


    void on_button_showTheSol_clicked();



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
