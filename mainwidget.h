#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "settingdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class mainWidget; }
QT_END_NAMESPACE

class mainWidget : public QWidget
{
    Q_OBJECT

public:
    mainWidget(QWidget *parent = nullptr);
    ~mainWidget();

private slots:
    void on_b_setting_clicked();

private:
    Ui::mainWidget *ui;
};
#endif // MAINWIDGET_H
