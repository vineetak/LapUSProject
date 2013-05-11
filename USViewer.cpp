#include "USViewer.h"
#include <iostream>
USViewer::USViewer(void){




}

USViewer::USViewer(QWidget* parent){
	std::cout<<"Creating the US viewer widget......\n";

	this->setParent(parent);

	/* Create the US image label */
	imageLabelUS = new QLabel;
  //  imageLabelUS->setBackgroundRole(QPalette::Base);
    //imageLabelUS->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Ignored);
    imageLabelUS->setScaledContents(true);
    //imageLabelUS->setBaseSize(QSize(100,100));
	imageLabelUS->setMinimumSize(75*4/3*4,75*4);
    
    scrollAreaUS = new QScrollArea;
    //scrollAreaUS->setBackgroundRole(QPalette::Dark);
    scrollAreaUS->setWidget(imageLabelUS);
    scrollAreaUS->setAlignment(Qt::AlignCenter);
    scrollAreaUS->setFixedSize(80*4/3*4,80*4);

    // Live image
    imageLabelLive = new QLabel;
    //imageLabelLive->setBackgroundRole(QPalette::Base);
    //imageLabelLive->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabelLive->setScaledContents(true);
	imageLabelLive->setMinimumSize(75*4/3*4,75*4);
	// Scroll Area to display the live image
    scrollAreaLive = new QScrollArea;
    scrollAreaLive->setFixedSize(80*4/3*4,80*4);
    //scrollAreaLive->setBackgroundRole(QPalette::Dark);
    scrollAreaLive->setWidget(imageLabelLive);
    scrollAreaLive->setAlignment(Qt::AlignCenter);


   // QVBoxLayout *layout = new QVBoxLayout(this);
	QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setSpacing(0);
    layout->addWidget(scrollAreaUS);
    layout->addWidget(scrollAreaLive);
}
QLabel* USViewer::getTheUSImageLabel(){
	return imageLabelUS;
}
QLabel* USViewer::getTheLiveImageLabel(){
	return imageLabelLive;
}
USViewer::~USViewer(void){


	
}