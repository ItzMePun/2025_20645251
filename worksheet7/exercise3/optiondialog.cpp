#include "optiondialog.h"
#include "ui_optiondialog.h"

optionDialog::optionDialog(QWidget *parent, ModelPart *part)
    : QDialog(parent)
    , ui(new Ui::optionDialog)
{
    ui->setupUi(this);
    ui->nameEdit->setText(part->data(0).toString());
    ui->rEdit->setValue(part->data(2).value<QColor>().red());
    ui->gEdit->setValue(part->data(2).value<QColor>().green());
    ui->bEdit->setValue(part->data(2).value<QColor>().blue());
    ui->isVisible->setChecked(part->data(1).toString().compare("true", Qt::CaseInsensitive) == 0);
}

optionDialog::~optionDialog()
{
    delete ui;
}

QString optionDialog::getName()
{
    return ui->nameEdit->text();
}

bool optionDialog::getVisible()
{
    return ui->isVisible->isChecked();
}

QColor optionDialog::getColor()
{
    QColor color(ui->rEdit->value(), ui->gEdit->value(), ui->bEdit->value());
    return color;
}
