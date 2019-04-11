//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#ifndef HUGGLEPARSER_HPP
#define HUGGLEPARSER_HPP

#include "definitions.hpp"

#include <QString>
#include <QDateTime>
#include <QList>
#include <QVariant>
#include "hugglequeuefilter.hpp"

namespace YAML
{
    class Node;
}

namespace Huggle
{
    class Configuration;
    class UserConfiguration;
    class ProjectConfiguration;
    class HuggleQueueFilter;
    class WikiSite;

    //! This namespace contains functions to parse various text, such as configuration keys
    namespace HuggleParser
    {
        //! Returns default value in case that obtained value is empty, prevents issues where user configuration has empty keys
        //! or even where the converted config from previous versions had empty values
        HUGGLE_EX_CORE QString UserConfig_NonEmpty(const QString& key, const QString& value, const QString& default_val);
        //! Parse a string from configuration which has format used by huggle 2x
        /*!
         * \param key Key
         * \param content Text to parse from
         * \param missing Default value in case this key is missing in text
         * \param non_empty if true value of key must be non empty. If empty default value is returned instead. Expected to be used when parsing
         *                  user config only.
         * \return Value of key, in case there is no such a key content of missing is returned
         */
        HUGGLE_EX_CORE QString ConfigurationParse(const QString &key, const QString &content, const QString &missing = "", bool non_empty = false);
        HUGGLE_EX_CORE bool ConfigurationParseBool(const QString &key, const QString &content, bool missing);
        HUGGLE_EX_CORE bool YAML2Bool(const QString& key, YAML::Node &node, bool missing = false);
        HUGGLE_EX_CORE QString YAML2String(const QString& key, YAML::Node &node, const QString &missing = "", bool non_empty = false);
        HUGGLE_EX_CORE int YAML2Int(const QString& key, YAML::Node &node, int missing = 0);
        HUGGLE_EX_CORE unsigned int YAML2UInt(const QString& key, YAML::Node &node, unsigned int missing = 0);
        HUGGLE_EX_CORE double YAML2Double(const QString& key, YAML::Node &node, double missing = 0);
        HUGGLE_EX_CORE long long YAML2LongLong(const QString& key, YAML::Node &node, long long missing = 0);
        HUGGLE_EX_CORE QHash<QString, QVariant> YAML2QHash(const QString &key, YAML::Node &node, QHash<QString, QVariant> missing, bool *ok = nullptr);
        HUGGLE_EX_CORE QStringList YAML2QStringList(YAML::Node &node, bool *ok = nullptr);
        HUGGLE_EX_CORE QStringList YAML2QStringList(YAML::Node &node, QStringList missing, bool *ok = nullptr);
        HUGGLE_EX_CORE QStringList YAML2QStringList(const QString &key, YAML::Node &node, bool *ok = nullptr);
        HUGGLE_EX_CORE QStringList YAML2QStringList(const QString& key, YAML::Node &node, QStringList missing, bool *ok = nullptr);
        HUGGLE_EX_CORE QHash<QString, QString> YAML2QStringHash(YAML::Node &node, bool *ok = nullptr);
        HUGGLE_EX_CORE QHash<QString, QString> YAML2QStringHash(const QString &key, YAML::Node &node, bool *ok = nullptr);
        HUGGLE_EX_CORE QHash<QString, QString> YAML2QStringHash(const QString &key, YAML::Node &node, QHash<QString, QString> missing, bool *ok = nullptr);
        HUGGLE_EX_CORE QHash<QString, QHash<QString, QString>> YAML2QHashOfHash(const QString& key, YAML::Node &node, bool *ok = nullptr);
        HUGGLE_EX_CORE QList<QStringList> YAML2QListOfQStringList(const QString& key, YAML::Node &node, bool *ok = nullptr);
        HUGGLE_EX_CORE QString FetchYAML(QString source, bool *failed = nullptr);
        //! \todo This function needs a unit test
        HUGGLE_EX_CORE QString GetSummaryOfWarningTypeFromWarningKey(const QString& key, ProjectConfiguration *project_conf, UserConfiguration *user_conf = nullptr);
        //! \todo This function needs a unit test
        HUGGLE_EX_CORE QString GetNameOfWarningTypeFromWarningKey(QString key, ProjectConfiguration *project_conf);
        //! \todo This function needs a unit test
        HUGGLE_EX_CORE QString GetKeyOfWarningTypeFromWarningName(QString id, ProjectConfiguration *project_conf);
        //! \todo This function needs a unit test
        /*!
         * \brief ConfigurationParse_QL Parses a QStringList of values for a given key
         * The list must be either separated by comma and newline or it can be a list of values separated
         * by comma only, however if you want to have multiple items per line, you need to set CS to true
         * \param key Key
         * \param content Text to parse key from
         * \param CS Whether the values are separated by comma only (if this is set to true there can be more items on a line)
         * \return List of values from text or empty list
         */
        HUGGLE_EX_CORE QStringList ConfigurationParse_QL(const QString &key, const QString &content, bool CS = false);
        //! \todo This function needs a unit test
        HUGGLE_EX_CORE QStringList ConfigurationParse_QL(const QString &key, const QString &content, QStringList list, bool CS = false);
        //! \todo This function needs a unit test
        //! Provides a QList from a value that has items separated by commas, each item on a line. The trailing comma will be trimmed.
        HUGGLE_EX_CORE QStringList ConfigurationParseTrimmed_QL(const QString &key, const QString &content, bool CS = false, bool RemoveNull = false);
        HUGGLE_EX_CORE QList<HuggleQueueFilter*> ConfigurationParseQueueList_YAML(YAML::Node &node, bool locked = false);
        //! \todo This function needs a unit test
        HUGGLE_EX_CORE QList<HuggleQueueFilter*> ConfigurationParseQueueList(QString content, bool locked = false);
        /*!
         * \brief GetIDOfMonth retrieve a month based on list of localized months in configuration file
         * \param month
         * \return If there is no such a month this function will return negative number
         */
        HUGGLE_EX_CORE byte_ht GetIDOfMonth(QString month, WikiSite *site);
        //! \todo This function needs a unit test
        //! Parse a part patterns for score words
        HUGGLE_EX_CORE void ParsePatterns(const QString &text, WikiSite *site);
        //! \todo This function needs a unit test
        HUGGLE_EX_CORE void ParseWords(const QString &text, WikiSite *site);
        HUGGLE_EX_CORE void ParseNoTalkWords(const QString &text, WikiSite *site);
        HUGGLE_EX_CORE void ParseNoTalkPatterns(const QString &text, WikiSite *site);
        //! Parse a part patterns for score words
        HUGGLE_EX_CORE void ParsePatterns_yaml(YAML::Node &node, WikiSite *site);
        HUGGLE_EX_CORE void ParseWords_yaml(YAML::Node &node, WikiSite *site);
        HUGGLE_EX_CORE void ParseNoTalkWords_yaml(YAML::Node &node, WikiSite *site);
        HUGGLE_EX_CORE void ParseNoTalkPatterns_yaml(YAML::Node &node, WikiSite *site);
        //! \todo This function needs a unit test
        HUGGLE_EX_CORE QString GetValueFromSSItem(QString item);
        //! \todo This function needs a unit test
        HUGGLE_EX_CORE QString GetKeyFromSSItem(QString item);
        /*!
         * \brief Process content of talk page in order to figure which user level they have
         * \param page The content of talk page
         * \return Level
         */
        HUGGLE_EX_CORE byte_ht GetLevel(QString page, QDate bt, Huggle::WikiSite *site);
    }
}

#endif // HUGGLEPARSER_HPP
