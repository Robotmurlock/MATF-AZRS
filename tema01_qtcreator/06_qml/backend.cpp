#include "backend.h"

#include <QDebug>
#include <QFile>

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    m_content = "";
}

QString BackEnd::content()
{
    return m_content;
}

void BackEnd::setContent(const QString &content)
{
    // Brise se sadrzaj i otvara se nova datoteka
    QFile file(content);
    m_content = "";
    // Ako datoteka ne postoji, sadrzaj ostaje prazan
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    // U suprotnom se cita sav sadrzaj
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        m_content += line;
    }
}
