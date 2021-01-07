#ifndef AITABLEMODEL_H
#define AITABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include "../ptcfg.h"

QT_FORWARD_DECLARE_CLASS(AiData);
class AiTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit AiTableModel(const QStringList &headers, QObject *parent = nullptr);
    explicit AiTableModel(const QStringList &headers, const QSharedPointer<PtCfg>& ptCfg, QObject *parent = nullptr);
    ~AiTableModel() override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void appendRow(const QModelIndex& parent = QModelIndex());

    void resetDatas(int num);
signals:

public slots:
    void randomNumber();

private:
    QStringList m_headers;
    QSharedPointer<PtCfg> m_ptCfg;
};

#endif // AITABLEMODEL_H
