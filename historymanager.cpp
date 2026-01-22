#include "historymanager.h"

HistoryManager* HistoryManager::m_instance = nullptr;
HistoryManager* HistoryManager::getInstance() {
    if (!m_instance) {
        m_instance = new HistoryManager();
    }
    return m_instance;
}
void HistoryManager::addRecord(const QString &record) {
    m_records.append(record);
    if (m_records.size() > 100) {
        m_records.removeFirst();
    }
}
QList<QString> HistoryManager::getRecords() const {
    return m_records;
}
void HistoryManager::clear() {
    m_records.clear();
}
int HistoryManager::count() const {
    return m_records.size();
}
