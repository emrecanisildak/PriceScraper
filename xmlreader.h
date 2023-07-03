#ifndef XMLREADER_H
#define XMLREADER_H

#include <QObject>
#include "xlsxdocument.h"

namespace QXlsx{
    class Document;
}

class XMLReader : public QObject
{
    Q_OBJECT
public:
    explicit XMLReader(QObject *parent = nullptr);

    void                     load(const QString &path);
    std::vector<QString>     readAllColumnn(int column);

private:
    QXlsx::Document* mXlsxR;

};

#endif // XMLREADER_H
