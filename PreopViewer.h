#pragma once
#include "c:\qt\4.8.4\src\gui\widgets\qtabwidget.h"
#include <QListWidget>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <iostream>
#include <QListWidget>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QApplication>
#include <QDesktopWidget>

class PreopViewer :
	public QWidget
{

private:
	QScrollArea* preOpscrollArea ;
    QLabel* preopimageLabel;
    QVBoxLayout *layout;	

public:
	PreopViewer(void);
	PreopViewer(QWidget* parent);
	void wheelEvent(QWheelEvent* wheelEvent);

	QLabel* getThePreopImageLabel();
	~PreopViewer(void);
};