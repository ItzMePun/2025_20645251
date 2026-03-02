#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include <QDialog>
#include "ModelPart.h"

namespace Ui {
class optionDialog;
}

class optionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit optionDialog(QWidget *parent = nullptr, ModelPart* part = nullptr);
    ~optionDialog();
    QString getName();
    bool getVisible();
    QColor getColor();

private:
    Ui::optionDialog *ui;
};

#endif // OPTIONDIALOG_H
