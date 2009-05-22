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

#ifndef GOOGLETRANSLATECONFIG_H
#define GOOGLETRANSLATECONFIG_H

#include <KCModule>

#include "ui_googletranslate_config.h"

class KConfigGroup;

class GoogleTranslateConfigForm : public QWidget, public Ui::GoogleTranslateUi
{
    Q_OBJECT
    public:
        explicit GoogleTranslateConfigForm(QWidget* parent);
};

class GoogleTranslateConfig : public KCModule
{
    Q_OBJECT
    public:
        explicit GoogleTranslateConfig(QWidget* parent = 0, const QVariantList& args = QVariantList());
        ~GoogleTranslateConfig();

    public slots:
        void save();
        void load();
        void defaults();

    private:
        KConfigGroup config() const;

    private:
        GoogleTranslateConfigForm* m_ui;
};

#endif
