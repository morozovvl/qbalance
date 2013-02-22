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

#ifndef __METASQL_H__
#define __METASQL_H__

#include <QString>

class QSqlDatabase;

#include <xsqlquery.h>
#include <parameter.h>

class MetaSQLQueryParser;
class MetaSQLQuery {
    public:
        MetaSQLQuery(const QString & = QString::null);
        virtual ~MetaSQLQuery();

        bool setQuery(const QString &);
        bool isValid();
        QString getSource();

        XSqlQuery toQuery(const ParameterList &, QSqlDatabase pDb = QSqlDatabase(), bool pExec = true);

        QString parseLog();

    private:
        MetaSQLQueryParser * _data;

        QString _source;
};

#endif

