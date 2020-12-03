#include "login.h"
#include "ui_login.h"


Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
{
    err = new ErrorDialog(this);
    autoLoginFlag = false;
    localLoader = new QFile(Ui::localAccountPath);
    username = new QString();
    password = new QString();
    localUsername = new QString();
    localPasswd = new QString();
    loadLocalAccount(*localUsername, *localPasswd);
    ui->setupUi(this);
    //connect(ui->BtnLogin, SIGNAL(clicked()), this, SLOT(on_BtnLogin_clicked()));
    lineEditInit();
}

Login::~Login()
{
    delete err;
    delete localPasswd;
    delete localUsername;
    delete username;
    delete password;
    delete localLoader;
    delete ui;
}


void Login::lineEditInit (void)
{
    if (localUsername->isEmpty() || localPasswd->isEmpty())
    {
        qDebug() << "No local account data" << endl;
        return;
    }

    ui->username_line->setText(*localUsername);
    ui->password_line->setText(*localPasswd);
    autoLoginFlag = true;
    ui->Btn_autoLogin->click();
}

void Login::showQTVersion (void)
{
    major = QT_VERSION_MAJOR;
    minor = QT_VERSION_MINOR;
    patch = QT_VERSION_PATCH;
    qDebug() << major << "." << minor << "." << patch << endl;
}

void Login::loadLocalAccount (QString &user, QString &passwd)
{
    localLoader->open(QIODevice::ReadOnly);
    if (!localLoader->isOpen())
    {
        qDebug() << "No local account info." << endl;

    }

    user =  QString(localLoader->readLine(Ui::maxNameSize));
    user.remove("\n");
    passwd = QString(localLoader->readLine(Ui::maxPasswdSize));
    passwd.remove("\n");
    localLoader->close();

}

void Login::on_BtnLogin_clicked()
{
    localLoader->open(QIODevice::WriteOnly);
    if (!localLoader->isOpen())
    {
        qDebug() << "No local account info." << endl;

    }

    qint64 ret;

    *username = ui->username_line->text();
    *password = ui->password_line->text();

    if (*username == Ui::currentUsername)
    {

        if (*password == Ui::currentPassword)
        {
            qDebug() << "Login successful." << endl
                     << "Username: " << *username << endl;

            ret = localLoader->write(username->toStdString().c_str(), username->length());
            if (ret == -1)
                return;
            else
                qDebug() << "Write " << ret << "bytes." << endl;

            ret = localLoader->write("\n");
            if (ret == -1)
                return;

            if (ui->Btn_rememPasswd->isChecked())
            {
                ret = localLoader->write(password->toStdString().c_str(), password->length());
                if (ret == -1)
                    return;
                else
                    qDebug() << "Write " << ret << "bytes." << endl;

                ret = localLoader->write("\n");
                if (ret == -1)
                    return;

                localLoader->close();
                qDebug() << "Saved Local Info." << endl;
                ErrorDialog *test = new ErrorDialog;
                test->setErrMsg("登陆成功");
                test->show();

                this->close();
                this->destroy();
                test->exec();
            }
        }
        else
        {
            qDebug() << "Password error!" << endl;
            qDebug() << *username << endl;
            qDebug() << *password << endl;
            *username = "";
            *password = "";
            localLoader->close();
            showErrorMsg("密码错误");
        }

    }
    else
    {
        qDebug() << "Username not exist!" << endl;
        qDebug() << *username << endl;
        qDebug() << *password << endl;
        *username = "";
        *password = "";
        localLoader->close();
        showErrorMsg("用户不存在");
    }


}

void Login::autoLogin(bool state)
{
    if (state)
        ui->BtnLogin->clicked();
}

void Login::showErrorMsg(const QString &msg)
{
    err->setErrMsg(msg);
    err->show();
}



