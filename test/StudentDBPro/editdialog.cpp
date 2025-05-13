#include "editdialog.h"
#include "ui_editdialog.h"
#include <QButtonGroup>


EditDialog::EditDialog(QWidget *parent, QSqlRecord *recp) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
    editRec = recp;
    ui->numEdit->setText(editRec->value("num").toString());
    ui->nameEdit->setText(editRec->value("name").toString());
    ui->ageEdit->setText(editRec->value("age").toString());
    ui->scoreEdit->setText(editRec->value("score").toString());
    ui->addressEdit->setText(editRec->value("city").toString());
    QButtonGroup *radioGroup = new QButtonGroup();
    radioGroup->addButton(ui->manRadio);
    radioGroup->addButton(ui->womenRadio);
    if(editRec->value("sex").toString().trimmed() == "男")
        ui->manRadio->setChecked(true);
    if(editRec->value("sex").toString().trimmed() == "女")
        ui->womenRadio->setChecked(true);
    QStringList cbList;
    cbList << "软件工程学院" << "岭南学院学院" << "外国语学院" << "计算机学院" << "自动化学院";
    cbList << "国际金融学院" << "航空航天学院" << "旅游学院" << "公共关系学院" << "数学系";
    ui->depcbBox->addItems(cbList);
    int pos = cbList.indexOf(editRec->value("department").toString());
    if(pos < 0) pos = -1;
    ui->depcbBox->setCurrentIndex(pos);
    ui->cancelBtn->setFocus();
    connect(ui->cancelBtn, &QPushButton::clicked, this, &EditDialog::close);
    //editRec->setValue("name", "good");
}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::on_updateBtn_clicked()
{   if(ui->manRadio->isChecked())
        editRec->setValue("sex", "男");
    if(ui->womenRadio->isChecked())
            editRec->setValue("sex", "女");
    editRec->setValue("age", ui->ageEdit->text().trimmed());
    editRec->setValue("score", ui->scoreEdit->text().trimmed());
    editRec->setValue("department", ui->depcbBox->currentText().trimmed());
    editRec->setValue("city", ui->addressEdit->text().trimmed());
    close();
}

