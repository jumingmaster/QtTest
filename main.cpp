#include "login.h"
#include "errordialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login login;

    /*登陆界面*/
    login.show();
    /*自动登录*/
    //login.autoLogin(login.autoLoginFlag);

    return a.exec();
}
