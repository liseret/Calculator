#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QString>
#include <QList>

class HistoryManager
{
private:
    static HistoryManager* m_instance;
    HistoryManager() = default;
    QList<QString> m_records;

public:
    HistoryManager(const HistoryManager&) = delete;
    HistoryManager& operator=(const HistoryManager&) = delete;
    static HistoryManager* getInstance();
    void addRecord(const QString &record);
    QList<QString> getRecords() const;
    void clear();
    int count() const;
};

#endif // HISTORYMANAGER_H
