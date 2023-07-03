#include "xmlreader.h"

#include <QDebug>
// [0] include QXlsx headers
//#include "xlsxchartsheet.h"
//#include "xlsxcellrange.h"
//#include "xlsxchart.h"
//#include "xlsxrichstring.h"
//#include "xlsxworkbook.h"

XMLReader::XMLReader(QObject *parent)
    : QObject{parent},
    mXlsxR{nullptr}
{

}

void XMLReader::load(const QString& pPath)
{
    using namespace QXlsx;

    if(!mXlsxR)
    {
        delete  mXlsxR;
    }

    mXlsxR = new Document(pPath);

    if ( mXlsxR->load() ) // load excel file
    {
        qDebug()<<"File loaded succesfully";
    }
    else
    {
        qDebug() << "[error] failed to load xlsx file.";
    }

}

std::vector<QString> XMLReader::readAllColumnn(int column)
{
    std::vector<QString> vals;
    using namespace QXlsx;

    auto rowMax = mXlsxR->dimension().rowCount();

    // TEST HAVE NO VALUE INSERT SPACE..
    for(int r = 0; r < rowMax+1; r++)
    {
        Cell* cell = mXlsxR->cellAt(r, column); // get cell pointer.
        if ( cell != NULL )
        {
            if(cell->readValue().isNull())
                continue;

            vals.push_back(cell->readValue().toString());

        }
        else
        {
            //vals.pus
        }
    }

    return vals;
}
