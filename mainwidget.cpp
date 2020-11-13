﻿#include "mainwidget.h"
#include "ui_mainwidget.h"


mainWidget::mainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainWidget)
{
    ui->setupUi(this);
    //默认参数初始化
    setting_file_path = QString("../settings2.txt");
    button_num = 6;
    //其余参数初始化
    log = "";
    buttons_name = QVector<QString>(button_num,"");
    buttons_command = QVector<QString>(button_num,"");
    //刷新设置
    fresh_settings();
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


/**
 * @brief mainWidget::fresh_settings：根据设置文件刷新设置
 */
void mainWidget::fresh_settings(){
    //读取现有txt，如果没有就创建一个
    QFile file(setting_file_path);
    if(file.open(QIODevice::ReadOnly)){
        //读文件
        ip_str = delete_enter(QString::fromLocal8Bit(file.readLine()));
        com_str = delete_enter(QString::fromLocal8Bit(file.readLine()));
        for (int i = 0;i<button_num;i++) {
            buttons_name[i] = delete_enter(QString::fromLocal8Bit(file.readLine()));
        }
        for (int i = 0;i<button_num;i++) {
            buttons_command[i] = delete_enter(QString::fromLocal8Bit(file.readLine()));
        }
        file.close();
        //打印log
        log_print_and_record(QString::fromLocal8Bit("读取已有设置文件：")+setting_file_path);
        log_print_and_record(QString::fromLocal8Bit("ip：")+ip_str);
        log_print_and_record(QString::fromLocal8Bit("com：")+com_str);
        qDebug()<<ip_str;
    }else{
        file.close();
        //直接赋默认值
        ip_str = "192.168.31.1";
        com_str = "8888";
        for (int i = 0;i<button_num;i++) {
            buttons_name[i] = QString::fromLocal8Bit("功能")+QString::number(i);
        }
        for (int i = 0;i<button_num;i++) {
            buttons_command[i] = QString::number(i);
        }
        //写文件
        if(file.open(QIODevice::WriteOnly)){
            file.write((ip_str+'\n').toLocal8Bit());
            file.write((com_str+'\n').toLocal8Bit());
            for (int i = 0;i<button_num;i++) {
                file.write((buttons_name[i]+'\n').toLocal8Bit());
            }
            for (int i = 0;i<button_num;i++) {
                file.write((buttons_command[i]+'\n').toLocal8Bit());
            }
        }
        file.close();
        //打印log
        log_print_and_record(QString::fromLocal8Bit("新建配置文件：")+setting_file_path+'\n');
        log_print_and_record(QString::fromLocal8Bit("ip：")+ip_str);
        log_print_and_record(QString::fromLocal8Bit("com：")+com_str);
    }
    //更新按键显示
    ui->b0->setText(buttons_name[0]);
    ui->b1->setText(buttons_name[1]);
    ui->b2->setText(buttons_name[2]);
    ui->b3->setText(buttons_name[3]);
    ui->b4->setText(buttons_name[4]);
    ui->b5->setText(buttons_name[5]);
}


/**
 * @brief mainWidget::delete_enter：去除字符串中第一个'\n'
 * @param str：输入字符串
 * @return 去回车后得字符串
 */
QString mainWidget::delete_enter(QString str){
    int n = str.size(),i=0;
    while (i<str.size()) {
        if(str[i]=='\n'||str[i]=='\r')str.remove(i,1);
        else i++;
    }
//    for (;i<n;i++) {
//        if(str[i]=='\n')break;
//    }
//    str.remove(i,1);
    return str;
}


/**
 * @brief mainWidget::log_print_and_record：记录本条log并打印在窗口上
 * @param tmp_log：本次录入log字符串
 */
void mainWidget::log_print_and_record(QString tmp_log){
    log.append(tmp_log);
    log.append('\n');
    ui->log_browser->append(tmp_log);
}
