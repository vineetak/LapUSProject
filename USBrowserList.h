#pragma once
#include "c:\qt\4.8.4\src\gui\widgets\qtabwidget.h"
#include <QListWidget>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <iostream>
#include <QListWidget>
#include <QDateTime>
#include "USBrowserListItem.h"
class USBrowserList :
	public QListWidget
{
	Q_OBJECT
private:

public:
	
	USBrowserList(void);
	//USBrowserList(QWidget* parent);
	~USBrowserList(void);
signals:

	void USitemClicked(USBrowserListItem* item);

};

