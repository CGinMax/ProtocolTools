#ifndef DITABLEMODEL_H
#define DITABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include "../ptcfg.h"

QT_FORWARD_DECLARE_CLASS(DiData);

class DiTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit DiTableModel(const QStringList& headers, QObject *parent = nullptr);
    explicit DiTableModel(const QStringList& headers, const QSharedPointer<PtCfg>& ptcfg, QObject *parent = nullptr);
    ~DiTableModel() override;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void insertRow(const DiData& diData, const QModelIndex& parent = QModelIndex());
    void resetDatas(int num);

    void setPtCfg(QSharedPointer<PtCfg>& ptcfg);

signals:

public slots:

private:
    QStringList m_headers;

    QSharedPointer<PtCfg> m_ptCfg;
};

#endif // DITABLEMODEL_H
