#include "mainwidget.h"
#include "ui_mainwidget.h"

mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainWidget)
{
    ui->setupUi(this);
}

mainWidget::~mainWidget()
{
    delete ui;
}


void mainWidget::on_b_setting_clicked()
{
    SettingDialog setting_dialog;
    setting_dialog.show();
    setting_dialog.exec();
}
