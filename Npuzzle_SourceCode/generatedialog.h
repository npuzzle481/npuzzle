#ifndef GENERATEDIALOG_H
#define GENERATEDIALOG_H
#include <QDialog>

namespace Ui {
class generateDialog;
}

class generateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit generateDialog(QWidget *parent = 0);
    ~generateDialog();

private:
    Ui::generateDialog *ui;
};

#endif // GENERATEDIALOG_H
