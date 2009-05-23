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


#include "googletranslate.h"
#include "googletranslatehttp.h"
#include "googletranslateutil.h"

#include <QClipboard>
#include <QLabel>
#include <QList>

#include <KApplication>
#include <KConfigGroup>
#include <KIcon>

GoogleTranslateRunner::GoogleTranslateRunner(QObject* parent, const QVariantList &args)
    : Plasma::AbstractRunner(parent, args)
{
    Q_UNUSED(args)
    setObjectName("Google Translate");
    setHasRunOptions(false);
    setIgnoredTypes(Plasma::RunnerContext::Directory |
                    Plasma::RunnerContext::File |
                    Plasma::RunnerContext::NetworkLocation |
                    Plasma::RunnerContext::Executable |
                    Plasma::RunnerContext::ShellCommand);

    addSyntax(Plasma::RunnerSyntax("gt=", i18n("Translate the word")));
}

GoogleTranslateRunner::~GoogleTranslateRunner()
{
}

void GoogleTranslateRunner::match(Plasma::RunnerContext &context)
{
    const QString term = context.query();

    if (!term.startsWith("gt=") || !term.endsWith("]"))
        return;

    GoogleTranslateHttp *http = new GoogleTranslateHttp();
    QString result = http->request(term, config().readEntry("fromLanguage", "en"),
                                         config().readEntry("toLanguage", "es"));

    if (http->hasError()) {
        Plasma::QueryMatch match(this);
        match.setType(Plasma::QueryMatch::InformationalMatch);

        match.setIcon(KIcon("dialog-error"));
        match.setText("Error : " + http->errorString());

        context.addMatch(term, match);
    }
    else {
        QStringList words = GoogleTranslateUtil::parseResult(result);

        foreach (const QString &word, words) {
            Plasma::QueryMatch match(this);
            match.setType(Plasma::QueryMatch::ExactMatch);

            match.setIcon(KIcon("dialog-ok-apply"));
            match.setText(word);

            context.addMatch(term, match);
        }
    }

    delete http;
}

void GoogleTranslateRunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)
    Q_UNUSED(match)

    kapp->clipboard()->setText(match.text());
}

#include "googletranslate.moc"
