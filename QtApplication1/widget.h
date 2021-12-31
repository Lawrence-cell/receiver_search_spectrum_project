#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//最小化相关
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include <QMenu>
#include <QAction>
//自定义弹窗
#include "mymessagebox.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void Paint();
    void Connext();
    ~Widget();

    int func1();

    

    int funcPage2();

    int funcPage3();

private slots:
    void closeEvent(QCloseEvent *event);

    void changeMboxReturn(int num);

    void on_btn_main_item_1_clicked();

    void on_btn_main_item_2_clicked();

    void on_btn_main_item_3_clicked();

    void on_btn_main_item_4_clicked();

    void on_btn_main_item_5_clicked();

    void on_btn_main_item_6_clicked();

    void on_btn_logout_clicked();

    void on_btn_littleshow_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_arbitrarySignalGenerate_LaunchBtn_clicked();

    void on_LTErunButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_19_clicked();

    void on_equalSignalRx_clicked();

    void on_singleDeviceSweep_Button_clicked();

    void on_singleDeviceSweep_LaunchBtn_clicked();

    void on_singleDeviceSweep_TimeTestBtn_clicked();

    void on_singleDeviceSweep_StartSweep_clicked();

    void on_averageSweep_clicked();

    void on_contSweep_clicked();

  
private:
    Ui::Widget *ui;
    QImage image;
    QString line;

    MyMessageBox *myMbox;
    //自定义窗口通信参数
    int mbox_return;

    //最小化到托盘
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    //窗口管理动作
    QAction *returnNormal;
    QAction *quitAction;

    void initUi();          //Ui界面初始化函数
    void initMember();      //成员变量初始化函数
    void littleShow();      //最小化显示函数
};

#endif // WIDGET_H
