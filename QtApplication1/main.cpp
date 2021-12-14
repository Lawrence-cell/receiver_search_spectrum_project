
#include "widget.h"
#include "appinit.h"
#include <QApplication>
#include <QFile>
#include <QFont>
#include "Dll1.h"
#include <QDebug>
#include <QLibrary>
//#include"testmain.h"
#include"windows.h"
//class MyThread : public QThread {
//     public:
//             virtual void run();
//    
//};
//
//     void MyThread::run()
//     {
//         for (int count = 0; count < 20; count++) {
//             sleep(1);
//             qDebug("Ping!");
//
//    }
//    }


//
//int widgetShow(int argc, char* argv[]) {
//    QApplication a(argc, argv);
//
//    //加载样式表
//    QFile file("C:/Users/yangguang/source/repos/QtApplication1V1/QtApplication1/css/index.css");
//    if (file.open(QFile::ReadOnly)) {
//
//        QString qss = QLatin1String(file.readAll());
//        qApp->setStyleSheet(qss);
//        file.close();
//    }
//
//
//    //全局字体
//    QFont font("Arial", 10);
//    a.setFont(font);
//
//    //屏幕拖动
//    AppInit::Instance()->start();
//
//    Widget w;
//    w.show();
//
//    return a.exec();
//
//}

int main(int argc, char *argv[])
{
   
   
    QApplication a(argc, argv);


    //加载样式表
    QFile file("C:/Users/yangguang/source/repos/QtApplication1V1/QtApplication1/css/index.css");
    if (file.open(QFile::ReadOnly)) {

        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        file.close();
    }


    //全局字体
    QFont font("Arial", 10);
    a.setFont(font);

    //屏幕拖动
    AppInit::Instance()->start();
    Widget w;
    
    //std::thread t(functionSwitch, 1);
    //线程间通信
    w.show();

    return a.exec();
  
    //function1();

   // std::thread a(widgetShow, argc, argv);
   // a.join();
    
}


