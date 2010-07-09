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
#include "googletranslateutil.h"

#include <QDebug>
#include <QMap>
#include <QRegExp>

#include <KGlobal>
#include <KLocale>

// QJSon
#include <qjson/parser.h>

bool GoogleTranslateUtil::isSearchTerm(const QString &term)
{
    if (term.contains("=")) {
        QPair <QString, QString> languages = getLanguages(term);
        return KGlobal::locale()->allLanguagesList().contains(languages.first) &&
               KGlobal::locale()->allLanguagesList().contains(languages.second);
    }

    return false;
}

QPair <QString, QString> GoogleTranslateUtil::getLanguages(const QString &term)
{
    int firstIndex = term.indexOf("=");
    int lastIndex  = term.lastIndexOf("");
    if (firstIndex > 0 && lastIndex > firstIndex) {
        return QPair<QString, QString>(term.left(firstIndex), term.right(term.size() - lastIndex + 1));
    }
    else {
        return QPair<QString, QString>("", "");
    }
}

QString GoogleTranslateUtil::getSearchWord(const QString &term)
{
    QRegExp rx("\\w{2,3}=(.*)=\\w{2,3}");
    QString value = "";

    int pos = rx.indexIn(term, 0);
    if (pos > -1) {
        value = rx.cap(1);
    }

    return value;
}

QStringList GoogleTranslateUtil::parseResult(const QString &text)
{
    QString jsonData = QString(text).replace(",,", ",");

    QStringList result;
    QJson::Parser parser;
    bool ok;
    qDebug() << "Parse result = " << text;
    QVariantList json = parser.parse(jsonData.toUtf8(), &ok).toList();
    if (ok) {
        foreach(const QVariant &data, json) {
            QVariantList list = data.toList();
            if (list.size() >= 1)
                result.append(getWordFromJson(list));
        }
    }
    else {
        result << "Error getting data : " << parser.errorString();
    }

    return result;
}

QString GoogleTranslateUtil::getWordFromJson(const QVariantList &json)
{
    QString result = "";

    result.append(json.at(0).toList().at(0).toString());

    if (json.at(0).toList().size() > 1) {
        QVariantList moreData = json.at(0).toList().at(1).toList();
        result.append(" : ");
        foreach(const QVariant &data, moreData) {
            result.append(" " + data.toString());
        }
    }

    return result;
}
