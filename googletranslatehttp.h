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

#ifndef GOOGLETRANSLATEHTTP_H
#define GOOGLETRANSLATEHTTP_H

#include <QEventLoop>
#include <QHttp>

/**
 * Ask google translate service synchronous
 */
class GoogleTranslateHttp : public QHttp
{
    Q_OBJECT
public:
    GoogleTranslateHttp(QObject *parent = 0);
    ~GoogleTranslateHttp();

    /**
     * Create the request and returs the translated words
     */
    QString request(const QString &text, const QString &fromLanguage, const QString &toLanguage);

private slots:
    void requestFinished();

private:
    QEventLoop loop;
};

#endif
