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

#include <QStringList>

QPair <QString, QString> GoogleTranslateUtil::getLanguages(const QString &term,
                                                           const QString &defaultFromLanguage,
                                                           const QString &defaultToLanguage)
{
    if (!term.contains("gt=[")) {
        QString languages = term.mid(3, term.indexOf("[") - 3);
        if (languages.indexOf(",") > 0) {
            QStringList languagesList = languages.split(",");
            return QPair <QString, QString> (languagesList [0], languagesList [1]);
        }
    }

    return QPair <QString, QString> (defaultFromLanguage, defaultToLanguage);
}

QString GoogleTranslateUtil::getSearchWord(const QString &term)
{
    return term.mid(term.indexOf("[") + 1, term.indexOf("]") - term.indexOf("[") - 1);
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
