/*
 *   Copyright (C) 2009 Javier Goday <jgoday@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License version 2 as
 *   published by the Free Software Foundation
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef GOOGLETRANSLATEUTIL_H
#define GOOGLETRANSLATEUTIL_H

#include <QList>
#include <QPair>
#include <QString>

class GoogleTranslateUtil
{
public:
    /**
     * returns true if term represents a valid search
     */
    static bool isSearchTerm(const QString &term);

    /**
     * Returns the languages for the search
     * manually in the search term (en=Hello es=)
     */
    static QPair <QString, QString> getLanguages(const QString &term);

    /**
     * Returns the search word from the runner search term (gt=[away])
     */
    static QString getSearchWord(const QString &term);

    /**
     * Returns a list of words as the result for the search
     */
    static QStringList parseResult(const QString &text);
};
#endif
