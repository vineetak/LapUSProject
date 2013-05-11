#pragma once
 
#include <QMainWindow>
#include <sawIntuitiveDaVinci/mtsIntuitiveDaVinci.h>
#include <cisstStereoVision.h>
#include <cisstStereoVisionQt.h>

#include <QWidget>
#include <QListWidget>
#include <QBoxLayout>
#include <qscrollbar.h>
#include <qscrollarea.h>
#include <QListWidgetItem>
#include <QFileInfo>
#include <QFileInfoList>
#include <qdir.h>
#include <QStringList>
#include "BrowserWidget.h"
#include "USViewer.h"
#include "PreopViewer.h"
#include "USBrowserListItem.h"
#include <QVBoxLayout>
#include <cisstStereoVision.h>
#include <cisstStereoVisionQt.h>
#include <QString>
#include <string>
#include <QDir>
#include <sstream>
#include "LapUSMouse.h"
#include <QAbstractItemView>
#include<QScrollBar>

class LapUSMainWindow : public QWidget
{ Q_OBJECT
private:
		// Video sources
	//svlFilterImageOpenGLQtWidget *vidWidget;
	//svlStreamManager streamUS;
	//svlFilterSourceVideoCapture sourceUS;
	//svlFilterImageFileWriter *writerUS;
	BrowserWidget* browserWidget;
	USViewer* USviewerWidget;
	PreopViewer* preopViewerWidget;
	QWidget* videoWidget;
	svlFilterImageFileWriter* USimagewriter;
	svlFilterImageFileWriter* Liveimagewriter;
	string saveFolderPath;
	mtsIntuitiveDaVinci *daVinci ;
	LapUSMouse* mouse ;
	int count;
	QPushButton * Save;
	//QWidget* videoSaveWidget;
	QWidget* justWidget;
	QPoint oldPos;
	bool released;
	bool clicked;
	QRect screenSize;
public:
	LapUSMainWindow(void);
	LapUSMainWindow::LapUSMainWindow(mtsIntuitiveDaVinci *daVinci,svlFilterImageOpenGLQtWidget *USVideoWidget,svlFilterImageFileWriter &USimagewriter,svlFilterImageFileWriter &Liveimagewriter,string saveFolderPath ="./SaveFolder");
	//LapUSMainWindow(svlFilterImageOpenGLQtWidget *vidWidget);
	~LapUSMainWindow(void);
protected:
	//virtual bool 	event ( QEvent * event );
	virtual void mouseMoveEvent ( QMouseEvent * event ) ;
	virtual bool event ( QEvent * event );

public slots:
  //  void showItem(USBrowserListItem *item1);
	void showItem(QListWidgetItem *item);
	void tabChanged(int);
    void showItemPreop    (QListWidgetItem *item);
	void saveImages();
	void mouseClicked(int x,int y);
	void mouseMoved(int x,int y);
	void mouseReleased();
};

