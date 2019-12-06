#ifndef MYMULTILIST_H
#define MYMULTILIST_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>

template <class T>
class MyMultiList
{
private:
    QList<QString>  list;
    QList<T>        valuesList;
public:
    MyMultiList();
    ~MyMultiList();
    void clear();
    void    append(QString, const T);
    void    insert(QString, const T);
    QStringList keys();
    QList<T> values(QString);
};



template <class T>
MyMultiList<T>::MyMultiList()
{
    clear();
}


template <class T>
MyMultiList<T>::~MyMultiList()
{
}


template <class T>
void  MyMultiList<T>::clear()
{
    list.clear();
    valuesList.clear();
}


template <class T>
void  MyMultiList<T>::append(QString key, const T value)
{
    list.append(key);
    valuesList.append(value);
}


template <class T>
void  MyMultiList<T>::insert(QString key, const T value)
{
    append(key, value);
}


template <class T>
QStringList MyMultiList<T>::keys()
{
    QStringList result;
    for (int i = 0; i < list.count(); i++)
    {
        if (!result.contains(list.at(i)))
        {
            result.append(list.at(i));
        }
    }
    return result;
}


template <class T>
QList<T> MyMultiList<T>::values(QString key)
{
    QList<T> result;
    for (int i = 0; i < list.count(); i++)
    {
        if (list.at(i) == key)
        {
            result.append(valuesList.at(i));
        }
    }
    return result;
}

#endif // MYMULTILIST_H
