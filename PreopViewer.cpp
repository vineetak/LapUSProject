#include "PreopViewer.h"
#include <iostream>
PreopViewer::PreopViewer(void){




}
void PreopViewer::wheelEvent(QWheelEvent* event){
	std::cout<<"Wheel Event occured";
//	qWarning() << Q_FUNC_INFO << event;
}
PreopViewer::PreopViewer(QWidget* parent){

    this->setStyleSheet("background-color:black;");
	std::cout<<"Creating thePreopViewer  widget......\n";
	this->setParent(parent);
	preOpscrollArea = new QScrollArea;
    QDesktopWidget *desk = QApplication::desktop();
    QRect screenSize;
    if(desk)
        screenSize = desk->screenGeometry(0);
    //preOpscrollArea->setBackgroundRole(QPalette::Dark);
    preopimageLabel = new QLabel;
    preopimageLabel->setMinimumSize(((screenSize.width()*3/4)-50),((screenSize.width()*3/4)-50)*650/1105);
    preOpscrollArea->setMinimumSize(((screenSize.width()*3/4)-20),((screenSize.width()*3/4)-20)*650/1105);
    //preOpscrollArea->setMinimumSize(screenSize.width()*3/4,screenSize.width()*3/4*650/1105);
    //preopimageLabel->setBaseSize(200,200);
    //preopimageLabel->setBackgroundRole(QPalette::Base);
   // preopimageLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    preopimageLabel->setScaledContents(true);
    preOpscrollArea->setWidget(preopimageLabel);
    preOpscrollArea->setStyleSheet("background-color:black;");


    layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->addWidget(preOpscrollArea,0,Qt::AlignCenter);
	
}
QLabel* PreopViewer::getThePreopImageLabel(){
	return preopimageLabel;
}
PreopViewer::~PreopViewer(void){


	
}