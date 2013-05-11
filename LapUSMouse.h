
#ifndef LapUS_3Dmouse_h
#define LapUS_3Dmouse_h



#include <QWidget>
//#include <QtGui/QCloseEvent>
#include <QTouchEvent>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>
//#include <QRec>
#include <QLabel>
#include <QPixmap>
#include <QCursor>
#include <QMouseEvent>

#include <cisstMultiTask.h>
//#include <cisstCommon.h>
//#include <cisstVector.h>
#include <cisstParameterTypes.h>
#include <cisstOSAbstraction.h>
#include <iostream>
//#if DAVINCI_ENABLED
#include <sawIntuitiveDaVinci/mtsIntuitiveDaVinci.h>
#include "LapUSCallbacks.h"



class LapUSMouse: public QLabel
{
    Q_OBJECT;
    
public:

	LapUSMouse(void);
	LapUSMouse(mtsIntuitiveDaVinci *daVinci,QWidget* mainWidget );
    ~LapUSMouse(void);
	void setupDaVinci(void);
	void updateDaVinci(void);
	//bool event(QEvent *event);	

private:

	// da Vinci 
	mtsIntuitiveDaVinci * daVinci;
	MyCallBacks callbacks;
	// right arm of the da vinci
	mtsInterfaceProvided * MTMR1_Interface;
	mtsFunctionRead GetPositionTipMTMR1;
	prmPositionCartesianGet arm_right;
	QTimer timer; 
	QRect screenSize;
	QCursor cursor ; 
	QWidget* mainWidget;

public slots:
	void updateMouse(void);

signals: 
	void pinched(int x,int y);
	void moved(int x,int y);
	void released();
};
#endif
