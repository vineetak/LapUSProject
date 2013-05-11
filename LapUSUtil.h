#include <QFileInfoList>
#include <QFileInfo>
#include <iostream>
#include <QListWidget>
#include <QDateTime>
#include <list>
class LapUSUtil 
{

private:
	//QListWidget* USBrowserList;
public:
	LapUSUtil(void);
	~LapUSUtil(void);

	static QString getTheLastModifiedFile(QDir d,QStringList filter);

};
