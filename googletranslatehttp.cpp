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

#include "googletranslatehttp.h"
#include "googletranslateutil.h"

#include <QHttpHeader>
#include <QHttpRequestHeader>

#include <QDebug>

GoogleTranslateHttp::GoogleTranslateHttp(QObject *parent) :
    QHttp(parent)
{
    connect(this, SIGNAL(done(bool)), SLOT(requestFinished()));
}

GoogleTranslateHttp::~GoogleTranslateHttp()
{
    loop.exit();
}

QString GoogleTranslateHttp::request(const QString &text, const QString &fromLanguage,
                                                          const QString &toLanguage)
{
    const QString &word = GoogleTranslateUtil::getSearchWord(text);
    qDebug() << "Searching " << word << " from = " << fromLanguage << " to = " << toLanguage;
    QString url = QString("/translate_a/t?client=t&sl="+
                           fromLanguage +
                           "&tl=" +
                           toLanguage);
    setHost("www.google.com");

    QHttpRequestHeader header = QHttpRequestHeader("POST", url, 1, 1);
    header.setValue("Host", "www.google.com");
    header.setValue("User-Agent", "Mozilla/5.0");
    header.setContentLength(word.length());

    QByteArray ba("text=");
    ba.append(word.toUtf8());
    QHttp::request(header, ba);

    loop.exec();
    return QString::fromUtf8(readAll());
}

bool GoogleTranslateHttp::hasError() const
{
    return error() != QHttp::NoError;
}

void GoogleTranslateHttp::requestFinished()
{
    loop.exit();
}
