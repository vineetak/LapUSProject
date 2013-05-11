#include "LapUSUtil.h"
#include <iostream>
#include <QDir>
#include <QStringList>

LapUSUtil::LapUSUtil(void)
{


}

QString LapUSUtil::getTheLastModifiedFile(QDir dir , QStringList filter){

//    filters << "US_*.bmp" ;
	dir.setNameFilters(filter);
	dir.setSorting(QDir::Time);
    QFileInfoList listUS = dir.entryInfoList();

    // Assuming that the first one is the last modified 
    // TODO check if this is correct
	QFileInfo fileInfo = listUS.at(0);
	QString fileName = fileInfo.absoluteFilePath();

	return fileName;
/*
    std::cout << "Finding the US files....." << std::endl;
    for (int i = 0; i < listUS.size(); ++i) {
        QFileInfo fileInfo = listUS.at(i);
		USFilelist.insert(fileInfo.absoluteFilePath());
    }
*/

}
