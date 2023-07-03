#ifndef EXPORTCONTROLLER_H
#define EXPORTCONTROLLER_H

#include <vector>
#include <refineddata.h>

class ExportController
{
public slots:
    static void onExportRequest(const std::vector<RefinedData>& data,const QString& path);
};

#endif // EXPORTCONTROLLER_H
