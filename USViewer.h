#pragma once
#include "c:\qt\4.8.4\src\gui\widgets\qtabwidget.h"
#include <QListWidget>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <iostream>
#include <QListWidget>
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
class USViewer :
	public QWidget
{

private:
	QLabel* imageLabelUS;
	QLabel* imageLabelLive;
	QScrollArea* scrollAreaUS;
	QScrollArea* scrollAreaLive;
public:
	USViewer(void);
	USViewer(QWidget* parent);
	QLabel* getTheUSImageLabel();
	QLabel* getTheLiveImageLabel();
	~USViewer(void);
};