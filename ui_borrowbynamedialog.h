/********************************************************************************
** Form generated from reading UI file 'borrowbynamedialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BORROWBYNAMEDIALOG_H
#define UI_BORROWBYNAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_borrowbynameDailog
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *boolname_lineEdit;

    void setupUi(QDialog *borrowbynameDailog)
    {
        if (borrowbynameDailog->objectName().isEmpty())
            borrowbynameDailog->setObjectName(QString::fromUtf8("borrowbynameDailog"));
        borrowbynameDailog->resize(400, 222);
        label = new QLabel(borrowbynameDailog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 60, 61, 16));
        pushButton = new QPushButton(borrowbynameDailog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(90, 180, 80, 21));
        pushButton_2 = new QPushButton(borrowbynameDailog);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 180, 80, 21));
        boolname_lineEdit = new QLineEdit(borrowbynameDailog);
        boolname_lineEdit->setObjectName(QString::fromUtf8("boolname_lineEdit"));
        boolname_lineEdit->setGeometry(QRect(140, 100, 113, 22));

        retranslateUi(borrowbynameDailog);

        QMetaObject::connectSlotsByName(borrowbynameDailog);
    } // setupUi

    void retranslateUi(QDialog *borrowbynameDailog)
    {
        borrowbynameDailog->setWindowTitle(QCoreApplication::translate("borrowbynameDailog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("borrowbynameDailog", "\350\257\267\350\276\223\345\205\245\344\271\246\345\220\215", nullptr));
        pushButton->setText(QCoreApplication::translate("borrowbynameDailog", "\347\241\256\345\256\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("borrowbynameDailog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class borrowbynameDailog: public Ui_borrowbynameDailog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BORROWBYNAMEDIALOG_H
