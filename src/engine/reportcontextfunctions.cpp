/************************************************************************************************************
Copyright (C) Morozov Vladimir Aleksandrovich
MorozovVladimir@mail.ru

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*************************************************************************************************************/

#ifndef REPORTFUNCTIONS_CPP
#define REPORTFUNCTIONS_CPP

#include <QObject>
#include <QScriptValue>
#include <QScriptContext>
#include <QScriptEngine>
#include <QDebug>

//-- функция SumToString -----------------------------------------------------------------------------------------------------
QString str0_9(QString n9, int strS) {
// обрабатываем числа от 1 до 9
    QString str9 = "";
    if (n9 == "1") {
        if (strS == 1)
            str9 = "один";
        else
            str9 = "одна";
    }
    else if (n9 == "2") {
        if (strS == 1)
            str9 = "два";
        else
            str9 = "две";
    }
    else if(n9 == "3")
        str9 = "три";
    else if (n9 == "4")
        str9 = "четыре";
    else if (n9 == "5")
        str9 = "пять";
    else if (n9 == "6")
        str9 = "шесть";
    else if (n9 == "7")
        str9 = "семь";
    else if (n9 == "8")
        str9 = "восемь";
    else if (n9 == "9")
        str9 = "девять";
    return str9;
}

QString str10_19(QString n19) {
// обрабатываем числа от 10 до 19
    QString str19 = "*****";
    if (n19 == "0")
        str19 = "десять";
    else if (n19 == "1")
        str19 = "одиннадцать";
    else if (n19 == "2")
        str19 = "двенадцать";
    else if (n19 == "3")
        str19 = "тринадцать";
    else if (n19 == "4")
        str19 = "четырнадцать";
    else if (n19 == "5")
        str19 = "пятнадцать";
    else if (n19 == "6")
        str19 = "шестнадцать";
    else if (n19 == "7")
        str19 = "семнадцать";
    else if (n19 == "8")
        str19 = "восемнадцать";
    else if (n19 == "9")
        str19 = "девятнадцать";
    return str19;
}

QString str20_90(QString n99) {
// обрабатываем числа от 20 до 90
    QString str99 = "*****";
    if (n99 == "2")
        str99 = "двадцать";
    else if (n99 == "3")
        str99 = "тридцать";
    else if (n99 == "4")
        str99 = "сорок";
    else if (n99 == "5")
        str99 = "пятьдесят";
    else if (n99 == "6")
        str99 = "шестьдесят";
    else if (n99 == "7")
        str99 = "семьдесят";
    else if (n99 == "8")
        str99 = "восемьдесят";
    else if (n99 == "9")
        str99 = "девяносто";
    return str99;
}

QString str_hund(QString nHund) {
// обрабатываем сотни
    QString strHund = "*****";
    if (nHund == "1")
        strHund = "сто";
    else if (nHund == "2")
        strHund = "двести";
    else if (nHund == "3")
        strHund = "триста";
    else if (nHund == "4")
        strHund = "четыреста";
    else if (nHund == "5")
        strHund = "пятьсот";
    else if (nHund == "6")
        strHund = "шестьсот";
    else if (nHund == "7")
        strHund = "семьсот";
    else if (nHund == "8")
        strHund = "восемьсот";
    else if (nHund == "9")
        strHund = "девятьсот";
    return strHund;
}

QString str0_999(QString strP_100, QString strP_10, QString strP_1, int strSex) {
// обрабатываем числа от 0 до 999
    QString str99, str100;
    if ((strP_100 == " ") || (strP_100 == "0"))
        str100 = "";
    else
        str100 = str_hund(strP_100);
    if ((strP_10 == " ") || (strP_10 == "0"))
        str99 = str0_9(strP_1, strSex);
    else {
        if (strP_10 == "1")
            str99 = str10_19(strP_1);
        else
            str99 = str20_90(strP_10) + " " + str0_9(strP_1, strSex);
    }
    str100 = QString(str100).trimmed();
    if (QString(str100).size() > 0)
        str100 = str100 + " ";
    return QString(str100 + str99).trimmed();
}

QScriptValue SumToString(QScriptContext* context, QScriptEngine* engine) {
    QString sResult = "";
    QScriptValue sumNum = context->argument(0);
    if (!sumNum.isNull() && sumNum.toNumber() != 0) {
        if (qAbs(sumNum.toInt32()) < 1000000000) {
            long long int nSumNum = int(sumNum.toInt32());
            int nCop = QVariant((sumNum.toNumber() - nSumNum) * 100).toInt();
            QString minus, unit1, unit2, unit3, unit4, unit5, unit6, strMld, strN_Mld, strMln, strN_Mln, strTh, strNTh, strHun, str, str1, str10, str100, strCop, sNum;
            minus = "";
            unit1 = "рубль";
            unit2 = "рубля";
            unit3 = "рублей";
            unit4 = "копейка";
            unit5 = "копейки";
            unit6 = "копеек";
            strMld = "";
            strMln = "";
            strTh = "";
            strHun = "";
            if (nSumNum >= 0)
                sNum = (nSumNum != 0 ? QString("%1").arg(nSumNum).trimmed() : "");
            else {
                minus = "минус";
                sNum = QString("%1").arg(qAbs(nSumNum)).trimmed();
            }
            int nLenNum = sNum.size();

            // числа меньше ста
            if (nLenNum < 3) {
                sNum = QString().fill(' ', 3 - nLenNum) + sNum;
                nLenNum = sNum.size();
            }
            str1 = sNum.at(nLenNum - 1);
            str10 = sNum.at(nLenNum - 2);
            str100 = sNum.at(nLenNum - 3);
            if (!((str1 == "0") && (str10 == "0") && (str100 == "0")))
                strHun = str0_999(str100, str10, str1, 1);

            // тысячи
            if (nLenNum > 3) {
                if (nLenNum < 6) {
                    sNum = QString().fill(' ', 6 - nLenNum) + sNum;
                    nLenNum = sNum.size();
                }
                str1 = sNum.at(nLenNum - 4);
                str10 = sNum.at(nLenNum - 5);
                str100 = sNum.at(nLenNum - 6);
                if (!((str1 == "0") && (str10 == "0") && (str100 == "0"))) {
                    strTh = str0_999(str100, str10, str1, 2);
                    if ((str1.toInt() == 1) && (str10 != "1"))
                        strNTh = "тысяча";
                    else {
                        if ((str1.toInt() > 1) && (str1.toInt() < 5) && (str10 != "1"))
                            strNTh = "тысячи";
                        else
                            strNTh = "тысяч";
                    }
                    strTh = strTh + " " + strNTh;
                }
            }

            // миллионы
            if (nLenNum > 6) {
                if (nLenNum < 9) {
                    sNum = QString().fill(' ', 9 - nLenNum) + sNum;
                    nLenNum = sNum.size();
                }
                str1 = sNum.at(nLenNum - 7);
                str10 = sNum.at(nLenNum - 8);
                str100 = sNum.at(nLenNum - 9);
                if (!((str1 == "0") && (str10 == "0") && (str100 == "0"))) {
                    strMln = str0_999(str100, str10, str1, 1);
                    if ((str1.toInt() == 1) && (str10 != "1"))
                        strN_Mln = "миллион";
                    else {
                        if ((str1.toInt() > 1) && (str1.toInt() < 5) && (str10 != "1"))
                            strN_Mln = "миллиона";
                        else
                            strN_Mln = "миллионов";
                    }
                    strMln = strMln + " " + strN_Mln;
                }
            }

            // миллиарды
            if (nLenNum > 9) {
                if (nLenNum < 12) {
                    sNum = QString().fill(' ', 12 - nLenNum) + sNum;
                    nLenNum = sNum.size();
                }
                str1 = sNum.at(nLenNum - 10);
                str10 = sNum.at(nLenNum - 11);
                str100 = sNum.at(nLenNum - 12);
                if (!((str1 == "0") && (str10 == "0") && (str100 == "0"))) {
                    strMld = str0_999(str100, str10, str1, 1);
                    if ((str1.toInt() == 1) && (str10 != "1"))
                        strN_Mld = "миллиард";
                    else {
                        if ((str1.toInt() > 1) && (str1.toInt() < 5) && (str10 != "1"))
                            strN_Mld = "миллиарда";
                        else
                            strN_Mld = "миллиардов";
                        }
                }
                strMld = strMld + " " + strN_Mld;
            }

            strMld = strMld.trimmed();
            if (strMld.size() > 0)
                strMld = strMld + " ";
            strMln = strMln.trimmed();
            if (strMln.size() > 0)
                strMln = strMln + " ";
            strTh = strTh.trimmed();
            if (strTh.size() > 0)
                strTh = strTh + " ";

            strHun = strHun.trimmed();
            if (sNum.size() > 0) {
                if (sNum.right(1) == "1")
                    strHun = (strHun.size() > 0 ? strHun + " ": "") + unit1;
                else if (QString("234").contains(sNum.right(1))) {
                    if ((sNum.right(2).toInt() > 10) && (sNum.right(2).toInt() < 15))
                        strHun = (strHun.size() > 0 ? strHun + " ": "") + unit3;
                    else
                        strHun = (strHun.size() > 0 ? strHun + " ": "") + unit2;
                }
                else if (QString("567890").contains(sNum.right(1)))
                    strHun = (strHun.size() > 0 ? strHun + " ": "") + unit3;
            }


            strCop = QString("00%1").arg(nCop).trimmed().right(2);
            if ((strCop.right(1) == "1") && !(nCop > 10 && nCop < 15))
                strCop = " " + strCop + " " + unit4;
            else if (QString("234").contains(strCop.right(1)) && !(nCop > 10 && nCop < 15))
                strCop = " " + strCop + " " + unit5;
            else if (QString("567890").contains(strCop.right(1)) || (nCop > 10 && nCop < 15))
                strCop = " " + strCop + " " + unit6;
            str = QString(minus + " " + strMld + strMln + strTh + strHun + strCop).trimmed();
            sResult = QString(QString(str).left(1) + QString(str).right(str.size() - 1));
        }
        else
            sResult = QObject::trUtf8("Слишком большое число");
    }
    return QScriptValue(engine, sResult);
}

//---------------------------------------------------------------------------------------------------------------------


#endif // REPORTFUNCTIONS_CPP



