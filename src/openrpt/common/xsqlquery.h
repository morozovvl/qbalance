/*
 * OpenRPT report writer and rendering engine
 * Copyright (C) 2001-2012 by OpenMFG, LLC
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 * Please contact info@openmfg.com with any questions on this license.
 */

#ifndef __XSQLQUERY_H__
#define __XSQLQUERY_H__

#include <QSqlQuery>
#include <QSqlRecord>
#include <datasource.h>

class XSqlQueryPrivate;
class QSqlError;


class XSqlQueryErrorListener {
  public:
    XSqlQueryErrorListener();
    virtual ~XSqlQueryErrorListener();
    virtual void error(const QString &, const QSqlError&) = 0;
};

class XSqlQuery : public QSqlQuery
{
  public:
    XSqlQuery();
    XSqlQuery(QSqlDatabase);
    XSqlQuery(QSqlResult *);
    XSqlQuery(const QString &, QSqlDatabase = QSqlDatabase());
    XSqlQuery(const QSqlQuery &);
    XSqlQuery(const XSqlQuery &);
    virtual ~XSqlQuery();
    XSqlQuery & operator=(const XSqlQuery &);

    virtual QVariant value(int i) const;
    virtual QVariant value(const QString &) const;

    virtual bool first();
    virtual bool next();
    virtual bool previous();
    virtual bool prev();

    virtual int count();

    virtual bool prepare(const QString &);

    virtual bool exec();
    bool exec(const QString &);

    virtual int findFirst(int, int);
    virtual int findFirst(const QString &, int);
    virtual int findFirst(const QString &, const QString &);

    void trackFieldTotal(QString &);
    double getFieldTotal(QString &);
    double getFieldSubTotal(QString &);
    void resetSubTotals();
    void resetSubTotalsCurrent();

    bool emulatePrepare() const;
    void setEmulatePrepare(bool);

    static void addErrorListener(XSqlQueryErrorListener*);
    static void removeErrorListener(XSqlQueryErrorListener*);
    static void setNameErrorValue(QString v);

  private:
    XSqlQueryPrivate * _data;
};

class XSqlQueryWrapper: public IDataSource
{
public:
    XSqlQueryWrapper() { Query = NULL; }

    XSqlQueryWrapper(XSqlQuery* query) {setQuery(query);}
    ~XSqlQueryWrapper()
    {
        if (Query)
        {
            delete Query;
            Query = NULL;
        }
    }

    inline XSqlQuery* query()                         const { return Query;}

    void setQuery(XSqlQuery* query) { Query = query;}

    virtual bool isValid()                            const {return Query->isValid()                ; }

    virtual int at()                                  const {return Query->at()                     ; }
    virtual int size()                                const {return Query->size()                   ; }

    virtual QVariant value(int i)                     const {return Query->value(i)                 ; }
    virtual QVariant value(const QString & name)      const {return Query->value(name)              ; }

    virtual bool first()                                    {return Query->first()                  ; }
    virtual bool next()                                     {return Query->next()                   ; }
    virtual bool previous()                                 {return Query->previous()               ; }
    virtual int count()                               const {return Query->count()                  ; }

    virtual QString fieldName(const int& index)       const {return Query->record().fieldName(index); }
    virtual int findFirst(int field, int target)            {return Query->findFirst(field, target) ; }
    virtual int findFirst(const QString & field, int target){return Query->findFirst(field, target) ; }
    virtual int findFirst(const QString & field, const QString &target) {return Query->findFirst(field, target) ; }

    virtual void trackFieldTotal(QString &field)                 {return Query->trackFieldTotal(field) ; }
    virtual double getFieldTotal(QString &field)                 {return Query->getFieldTotal(field)   ; }
    virtual double getFieldSubTotal(QString &field)              {return Query->getFieldSubTotal(field); }
    virtual void resetSubTotals()                                {return Query->resetSubTotals()       ; }
    virtual void resetSubTotalsCurrent()                         {return Query->resetSubTotalsCurrent(); }
private:

    XSqlQuery* Query;
};

#endif
