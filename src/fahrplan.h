/*******************************************************************************

    This file is a part of Fahrplan for maemo 2009-2012

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

*/

#ifndef FAHRPLAN_H
#define FAHRPLAN_H

#include <QObject>
#include <QSettings>
#include "fahrplan_backend_manager.h"
#include "fahrplan_favorites_manager.h"
#include "calendarthreadwrapper.h"

class Fahrplan : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ParserAbstract *parser READ parser)
    Q_PROPERTY(FahrplanFavoritesManager *favorites READ favorites)
    Q_PROPERTY(QString parserName READ parserName)
    Q_PROPERTY(QString version READ getVersion)

    public:
        explicit Fahrplan(QObject *parent = 0);
        ParserAbstract* parser();
        FahrplanFavoritesManager* favorites();
        QString parserName();
        QString getVersion();

    public slots:
        QStringList getParserList();
        void setParser(int index);
        void storeSettingsValue(const QString &key, const QString &value);
        QString getSettingsValue(const QString &key, const QString &defaultValue);
        void addJourneyDetailResultToCalendar(JourneyDetailResultList *result);

    signals:
        void parserStationsResult(StationsResultList *result);
        void parserJourneyResult(JourneyResultList *result);
        void parserJourneyDetailsResult(JourneyDetailResultList *result);
        void parserTimeTableResult(TimeTableResultList *result);
        void parserErrorOccured(const QString &msg);
        void parserChanged(const QString &name, int index);
        void favoritesChanged(const QStringList &favorites);
        void addCalendarEntryComplete(bool success);

    private slots:
        void onStationsResult(StationsResultList *result);
        void onJourneyResult(JourneyResultList *result);
        void onJourneyDetailsResult(JourneyDetailResultList *result);
        void onTimeTableResult(TimeTableResultList *result);
        void onErrorOccured(const QString &msg);
        void onParserChanged(const QString &name, int index);
        void onFavoritesChanged(const QStringList &favorites);

    private:
        static FahrplanBackendManager *m_parser_manager;
        static FahrplanFavoritesManager *m_favorites_manager;
        QSettings *settings;
};
#endif // FAHRPLAN_H
