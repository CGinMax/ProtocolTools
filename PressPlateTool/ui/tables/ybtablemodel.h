#ifndef YBTABLEMODEL_H
#define YBTABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QAbstractListModel>
class YBTableModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit YBTableModel(const QStringList& headers, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void append();

signals:

public slots:

private:
    QStringList m_headers;
    QStringList dataList;

};

#endif // YBTABLEMODEL_H
