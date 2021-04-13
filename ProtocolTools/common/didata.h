#ifndef DIDATA_H
#define DIDATA_H

#include <QObject>

class DiData : public QObject
{
    Q_OBJECT
public:
    explicit DiData(QObject *parent = nullptr);
    explicit DiData(int io, const QString& name, bool value, QObject *parent = nullptr);
    ~DiData() = default;

    DiData(const DiData& other);
    DiData& operator=(const DiData& other);
    DiData(DiData&& other) noexcept;
    DiData& operator=(DiData&& other) noexcept;

    inline void setIo(int io);
    inline int io() const;
    inline void setName(const QString& name);
    inline QString name() const;
    inline void setValue(bool value);
    inline bool value() const;

signals:

public slots:

private:
    int m_io{0};
    QString m_name{QString("Pt0")};
    bool m_value{false};
};

inline void DiData::setIo(int io)
{
    m_io = io;
}

inline int DiData::io() const
{
    return m_io;
}

inline void DiData::setName(const QString &name)
{
    m_name = name;
}

inline QString DiData::name() const
{
    return m_name;
}

inline void DiData::setValue(bool value)
{
    m_value = value;
}

inline bool DiData::value() const
{
    return m_value;
}

#endif // DIDATA_H
