#pragma once
#include "c:\qt\4.8.4\src\gui\widgets\qtabwidget.h"
#include <QListWidget>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <iostream>
#include <QListWidget>
#include <QDateTime>
#include <list>
#include "LapUSUtil.h"
#include "USBrowserListItem.h"
#include <QString>
#include "USBrowserList.h"
#include <QMouseEvent>
#include <QAbstractItemView>
//#include "QsKineticScroller.h"

class BrowserWidget :
	public QTabWidget
{
	Q_OBJECT
//private:

public:
	//QListWidget* USBrowserList;
	//QListWidget* list;
	USBrowserList* list;
	QListWidget* list2;
//	QsKineticScroller *scroller;
//public:
	BrowserWidget(void);
	BrowserWidget::BrowserWidget(QWidget* parent);
	~BrowserWidget(void);
	//void wheelEvent(QWheelEvent* wheelEvent);
protected:
	void mouseMoveEvent ( QMouseEvent * event );

signals:
	void updateUSImage(QListWidgetItem* item);
	void updatePreopImage(QListWidgetItem* item);

public slots:
	void updateUSBrowser();
	//void Scroll();

};

