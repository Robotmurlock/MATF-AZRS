#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <qqml.h>
#include <QtQml>

class BackEnd : public QObject
{
    Q_OBJECT
    // Q_PROPERTY([TIP] [IME_POLJA] READ [GETTER] WRITE [SETTER] NOTIFY [SIGNAL])
    // READ je za citanje vrednosti sa backend-a
    // WRITE je za pisanje vrednosti na backend
    // NOTIFY je tu kako bi se znalo da je vrednost promenjena

    // Kada se izvrsi operacija oblika:
    // ... = backent.content, u pozaditi se poziva ono sto je pod READ tj. getter

    // Kada se izvrsi operacija oblika:
    // backent.content = "...", u pozadini se poziva ono sto je pod WRITE tj.
    // setter i kada se postavi vrednost emituje se NOTIFY signal

    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)

public:
    BackEnd(QObject *parent = nullptr);

    QString content();
    void setContent(const QString &content);

signals:
    void contentChanged();

private:
    QString m_userName;
    QString m_content;
};

#endif // BACKEND_H
