#ifndef LOGIN_H
#define LOGIN_H
#include <QDebug>
#include <QFile>
#include <QWidget>
#include "errordialog.h"

//QT_BEGIN_NAMESPACE
namespace Ui
{
const QString localAccountPath = "/Users/henryzeng/learn-account.info";
static QString currentUsername = "chienheng";
static QString currentPassword = "h990611";
const qint16 maxNameSize = 16;
const qint16 maxPasswdSize = 16;

class Login;
}
//QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();
    void showQTVersion (void);
    bool autoLoginFlag;
    void autoLogin (bool);
    void showErrorMsg(const QString &msg);

private slots:
    void on_BtnLogin_clicked();

private:
    Ui::Login *ui;
    ErrorDialog *err;
    QFile *localLoader;
    uint16_t major;
    uint16_t minor;
    uint16_t patch;
    QString *username;
    QString *password;
    QString *localUsername;
    QString *localPasswd;
    void lineEditInit (void);
    void loadLocalAccount (QString &user, QString &passwd);


signals:
    void password_err();

};
#endif // LOGIN_H
