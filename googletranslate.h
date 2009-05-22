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

#ifndef GOOGLETRANSLATE_H
#define GOOGLETRANSLATE_H

#include <KGenericFactory>

#include <plasma/abstractrunner.h>

class GoogleTranslateHttp;

/**
 * Translate a word or sentence using google translate service http://translate.google.com/
 * the word or sentence must go between parenthesis
 * Can specify manually the languages before the word => gt=en,es[]
 */
class GoogleTranslateRunner : public Plasma::AbstractRunner
{
Q_OBJECT

public:
    GoogleTranslateRunner(QObject* parent, const QVariantList &args);
    ~GoogleTranslateRunner();

    void match(Plasma::RunnerContext &context);
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &action);
};

K_EXPORT_PLASMA_RUNNER(googletranslate, GoogleTranslateRunner)

#endif
