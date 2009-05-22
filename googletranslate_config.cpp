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

#include "googletranslate_config.h"

#include <QVBoxLayout>

#include <KConfigGroup>
#include <KGlobal>
#include <KPluginFactory>
#include <KPluginLoader>

#include <plasma/abstractrunner.h>

K_EXPORT_RUNNER_CONFIG(googletranslate, GoogleTranslateConfig)

GoogleTranslateConfigForm::GoogleTranslateConfigForm(QWidget* parent) : QWidget(parent)
{
    setupUi(this);
}

GoogleTranslateConfig::GoogleTranslateConfig(QWidget* parent, const QVariantList& args) :
        KCModule(ConfigFactory::componentData(), parent, args)
{
    m_ui = new GoogleTranslateConfigForm(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    setLayout(layout);

    layout->addWidget(m_ui);

    connect(m_ui->m_fromLanguage, SIGNAL(textChanged(QString)), SLOT(changed()));
    connect(m_ui->m_toLanguage, SIGNAL(textChanged(QString)), SLOT(changed()));

    load();
}

GoogleTranslateConfig::~GoogleTranslateConfig()
{
}

void GoogleTranslateConfig::load()
{
    m_ui->m_fromLanguage->setText(config().readEntry("fromLanguage", "en"));
    m_ui->m_toLanguage->setText(config().readEntry("toLanguage", "es"));

    emit changed(false);
}

void GoogleTranslateConfig::save()
{
    config().writeEntry("fromLanguage", m_ui->m_fromLanguage->text());
    config().writeEntry("toLanguage", m_ui->m_toLanguage->text());

    config().sync();

    emit changed(false);
}

void GoogleTranslateConfig::defaults()
{
    m_ui->m_fromLanguage->setText("en");
    m_ui->m_toLanguage->setText("es");

    emit changed(true);
}

KConfigGroup GoogleTranslateConfig::config() const
{
    KConfigGroup runners(KGlobal::config(), "Runners");
    return KConfigGroup(&runners, "Google Translate");
}

#include "googletranslate_config.moc"
