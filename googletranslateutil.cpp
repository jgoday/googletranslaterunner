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

#include <QRegExp>
#include <QStringList>

#include <KGlobal>
#include <KLocale>

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
    QRegExp rx("(\\w{2})=");
    QString fromLanguage = "";
    QString toLanguage = "";

    if (rx.indexIn(term, 0) != -1) {
        fromLanguage = rx.cap(1);
        int pos = rx.matchedLength();
        if (rx.indexIn(term, pos) != -1 &&
            KGlobal::locale()->allLanguagesList().contains(rx.cap(1))) {
            toLanguage = rx.cap(1);
        }
    }

    return QPair <QString, QString> (fromLanguage, toLanguage);
}

QString GoogleTranslateUtil::getSearchWord(const QString &term)
{
    QRegExp rx("\\w{2}=(.+)\\w{2}=");
    QString value = "";

    int pos = rx.indexIn(term, 0);
    if (pos > -1) {
        value = rx.cap(1);
    }
    return value;
}

QStringList GoogleTranslateUtil::parseResult(const QString &text)
{
    // TODO : use a real json parser
    QStringList result;
    QString firstResult = "";

    if (text.contains(",")) {
        firstResult = text.mid(2, text.indexOf(",") - 3);
    }
    else {
        firstResult = text.mid(1, text.size() - 2);
    }

    int index = firstResult.size() + 5;
    while (text.indexOf('[', index) > 0) {
        int endIndex = text.indexOf(']', index);

        QString words = text.mid(index + 1, endIndex - index - 1);
        result << words;

        index = text.indexOf('[', index + 1);
    }

    result << firstResult;

    return result;
}
