#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <QObject>
#include <QVariantMap>
#include "gathercontroller.h"
#include "gatherconfiguremodel.h"

class ControllerManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(GatherConfigureModel* gatherModel READ gatherModel WRITE setGatherModel)
public:
    explicit ControllerManager(QObject *parent = nullptr);
    ~ControllerManager() override;

    Q_INVOKABLE void addGatherConfig(int count, const QVariantMap& map);

    Q_INVOKABLE void removeController(int index);

    Q_INVOKABLE void queryVersion(int index);

    Q_INVOKABLE void configureAddress(int index, int addr);

    Q_INVOKABLE void configureSensorCount(int index, int count);

    Q_INVOKABLE bool toggleCommunication(int index);

    Q_INVOKABLE bool isConnected(int index);

    void setGatherModel(GatherConfigureModel* model);
    GatherConfigureModel* gatherModel();

signals:

public slots:

private:
    bool isOutOfRange(int index);

    QList<QSharedPointer<GatherController>> _controllers;
    GatherConfigureModel* _gatherModel;
};

#endif // CONTROLLERMANAGER_H
