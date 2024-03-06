#include "sentbook.h"
#include "ui_sentbook.h"

sentbook::sentbook(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sentbook)
{
    ui->setupUi(this);
}

sentbook::~sentbook()
{
    delete ui;
}
