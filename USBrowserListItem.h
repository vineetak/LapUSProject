#pragma once
#include "c:\qt\4.8.4\src\gui\widgets\qtabwidget.h"
#include <QListWidget>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <iostream>
#include <QListWidget>
#include <QDateTime>
#include <QPixmap>
#include <QPainter>
class USBrowserListItem :
	public QListWidgetItem
{

private:
	/* US image file path */
	QString USFile;
	/* Live image file path */
	QString LiveFile;
	/* List item icon */
	QIcon icon;
public:
	USBrowserListItem(QString,QString);
	USBrowserListItem(void);
	//USBrowserList(QWidget* parent);
	~USBrowserListItem(void);
	QString getLiveFile();
	QString getUSFile();
};

