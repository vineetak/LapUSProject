#include "LapUSMainWindow.h"

LapUSMainWindow::LapUSMainWindow(void){

}

LapUSMainWindow::LapUSMainWindow(mtsIntuitiveDaVinci *daVinci,svlFilterImageOpenGLQtWidget *USVideoWidget,svlFilterImageFileWriter &USimagewriter1,svlFilterImageFileWriter &Liveimagewriter1,string saveFolderPath)
{
	clicked = false ;
	released = false;
//	int argc = 0;
//	char **argv;
//	QApplication app(argc, argv);
	this->daVinci = daVinci;
	this->saveFolderPath = saveFolderPath;
	this->setWindowState(Qt::WindowFullScreen);
	setMouseTracking(true);
	count = 1;
	USimagewriter = &USimagewriter1;
	Liveimagewriter = &Liveimagewriter1;
	std::cout<<"Creating the main window......\n";
	/* -------------Create the browser tabs -----------------*/
	browserWidget = new BrowserWidget(this);

	/*--------------Create the US + Real Image Viewer-------*/
	USviewerWidget = new USViewer(this);

	/*-------------Create the preop image viewer -------*/
	preopViewerWidget = new PreopViewer(this);

	/* Create the LapUS mouse */
//	mouse = new LapUSMouse(daVinci); 

    //this->setStyleSheet("background-color:black;");


	/*-------------- Create the video widget ------------------*/

	QHBoxLayout* videoLayout = new QHBoxLayout();//(QBoxLayout::LeftToRight);
	videoLayout->setMargin(0);
	videoLayout->setSpacing(0);
	//videoLayout->addWidget(USVideoWidget,4,Qt::AlignCenter);
	videoLayout->addWidget(USVideoWidget,4);
	//USVideoWidget->setFixedSzie(400,400);

	// contains the video and the save button
	videoWidget = new QWidget();
	videoWidget->setParent(this);
//	videoWidget->setFixedSize(380,380);
	//videoWidget->setFixedSize(400,380);

	//QPushButton * Save = new QPushButton();
	Save = new QPushButton();
	Save->setFixedSize(120,50);
	Save->setText("Save");
	connect(Save,SIGNAL(clicked()),this,SLOT(saveImages()));
	Save->setStyleSheet("QPushButton { background-color:gray; font-size: 14pt}");//" qlineargradientx1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde}");
 
	videoWidget->setLayout(videoLayout);

	justWidget = new QWidget();
	//QVBoxLayout* ll = new QVBoxLayout();
	QHBoxLayout* ll = new QHBoxLayout();
	ll->addWidget(videoWidget);
	ll->addWidget(Save,0,Qt::AlignRight | Qt::AlignVCenter);
	justWidget->setLayout(ll);
	ll->setMargin(0);
	ll->setSpacing(0);


	// QWidget* justWidget = new QWidget();
	// QVBoxLayout* ll = new QVBoxLayout();
	// ll->addWidget(videoWidget);
	// ll->addWidget(Save,0,Qt::AlignBottom | Qt::AlignHCenter);
	// justWidget->setLayout(ll);

	//	videoWidget->show();
	//videoWidget->setMinimumSize(400,400);
	//videoWidget->setGeometry(0,0,350,350);
	//videoWidget->setFixedSize(350,350);  // TODO set it up according to the screen size 
	/*-------------- Create a the left widget containing the video , USViewer and preop ------------------*/


	QDesktopWidget *desk = QApplication::desktop();
//	QRect screenSize;
	if(desk)
     	screenSize = desk->screenGeometry(0);

    std::cout<<"Printing the screen geometry x :";
    std::cout<<screenSize.x() <<"y : "<<screenSize.y();
    std::cout<<"\n";

//	USviewerWidget->hide();
	preopViewerWidget->hide();
	//videoWidget->show();
	//videoWidget->setFixedSize(400,400);


	// QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	// sizePolicy.setHeightForWidth(true);
	// videoWidget->setSizePolicy(sizePolicy);

	/* add the video widget , USviewer and the preopview in a layout*/
    // QGridLayout *leftLayout = new QGridLayout();
    // leftLayout->addWidget(videoWidget,0,0);
    // leftLayout->addWidget(USviewerWidget,1,0);
    // leftLayout->addWidget(preopViewerWidget,1,0);
    
    //QVBoxLayout *leftLayout = new QVBoxLayout();
    //leftLayout->addWidget(videoWidget,1,Qt::AlignTop);
	//leftLayout->addWidget(USviewerWidget,1);
   // leftLayout->addWidget(preopViewerWidget,1);



    
    QWidget* viewerWidget = new QWidget(this);
    QVBoxLayout *viewerLayout = new QVBoxLayout();
    viewerLayout->addWidget(USviewerWidget);
    viewerLayout->addWidget(preopViewerWidget);
    viewerLayout->setSpacing(0);
	viewerLayout->setMargin(0);


    viewerWidget->setLayout(viewerLayout);
    
	QWidget* leftWidget = new QWidget();
    //QHBoxLayout* leftLayout = new QHBoxLayout();
    QVBoxLayout* leftLayout = new QVBoxLayout();
//    leftLayout->addWidget(videoWidget,1);
    leftLayout->addWidget(justWidget,2);
    leftLayout->addWidget(viewerWidget,1);
    leftLayout->setSpacing(0);
    leftLayout->setMargin(0);

    leftWidget->setLayout(leftLayout);

    leftWidget->setFixedSize(((screenSize.width()*3/4)-10),screenSize.height());
	videoWidget->setFixedSize(screenSize.height()*5/8*4/3,screenSize.height()*5/8);


	//USviewerWidget->hide();
	/*-------------------- Add the top widget and the browser widget to the mainlayout-----------------------*/
    //QGridLayout *mainLayout = new QGridLayout();
    QHBoxLayout* mainLayout = new QHBoxLayout();
//    mainLayout->addWidget(topWidget,0,Qt::AlignTop);
//    mainLayout->addWidget(leftWidget,0,Qt::AlignLeft);

    mainLayout->addWidget(leftWidget,7,Qt::AlignLeft);
    //mainLayout->setSpacing(0);
    //mainLayout->addWidget(browserWidget,0,Qt::AlignBottom);
    mainLayout->addWidget(browserWidget,0,Qt::AlignRight);
    //mainLayout->addWidget(rightWidget,2,Qt::AlignRight);
    //this->setLayout(layout);
    // viewerWidget->setLayout(layout);
    this->setLayout(mainLayout);
	this->show();

	USviewerWidget->setStyleSheet("background-color:black;");
    leftWidget->setStyleSheet("background-color:black;");
   // this->setStyleSheet("background-color:black;");


	/* Create new lap US mouse */
	mouse = new LapUSMouse(daVinci,this);
//	mouse->show();	

	connect(mouse,SIGNAL(pinched(int ,int) ),this,SLOT(mouseClicked(int,int)));
	connect(mouse,SIGNAL(moved(int ,int) ),this,SLOT(mouseMoved(int,int)));
	connect(mouse,SIGNAL(released()),this,SLOT(mouseReleased()));

	connect(browserWidget,SIGNAL(updateUSImage(QListWidgetItem*)),this,SLOT(showItem(QListWidgetItem*)));
	connect(browserWidget,SIGNAL(updatePreopImage(QListWidgetItem*)),this,SLOT(showItemPreop(QListWidgetItem*)));
//	app.exec();

	//connect(callbacks, pinched())
	//this->resize(600,500);
}

void LapUSMainWindow::mouseMoveEvent ( QMouseEvent * event ) {

//	std::cout<<"Overriding the mouse event \n";
	return QWidget::mouseMoveEvent(event);
}
bool LapUSMainWindow::event ( QEvent * event ){

	//cout<<"Main window geting the events .......\n";
 	switch (event->type()) {
			case QEvent::MouseMove:
            	//std::cout<<"mouse moving ...\n";
            	break;
			case QEvent::MouseButtonPress:
            	std::cout<<"Mouse pressed....\n";
            	break;
          //  default:
            //	std::cout<<"default ...";

//             if (!((QKeyEvent *)event)->isAccepted())
//                 return false;
//             break;

 	}
	return QWidget::event(event);
}
void LapUSMainWindow::showItemPreop(QListWidgetItem *item){

    if(preopViewerWidget->isHidden()){
        preopViewerWidget->show();
    }
    QIcon icon = item->icon();
    //QPixmap pixmap = icon.pixmap(QSize(400,300));
    QPixmap pixmap = icon.pixmap(((screenSize.width()*3/4)-50),((screenSize.width()*3/4)-50)*650/1105);
    //preOpscrollArea->setMinimumSize(((screenSize.width()*3/4)-50),((screenSize.width()*3/4)-50)*650/1105);

    preopViewerWidget->getThePreopImageLabel()->setScaledContents(true);
    preopViewerWidget->getThePreopImageLabel()->setPixmap(pixmap);
}

// TODO rename to showUS item

void LapUSMainWindow::showItem(QListWidgetItem *item1){
//void LapUSMainWindow::showItem(USBrowserListItem *item1){
 //   std::cout<<"Show the item";
    //item1->setBackgroundColor(QColor(255, 0, 0, 127));

    if(USviewerWidget->isHidden()){
        USviewerWidget->show();
    }

	if(item1){
		cout<<"US browser item received\n";
		USBrowserListItem *i = dynamic_cast<USBrowserListItem*>(item1);
		if(i){
			std::cout<<"This is actually a US Brwoser list item";

		//QIcon icon = item1->icon();
		//QPixmap pixmap = icon.pixmap(QSize(300,300));

		QString USfile = i->getUSFile();
		std::cout<<"Displaying the US image .." <<qPrintable(USfile);
		QPixmap pixmapUS(USfile);
		//pixmapUS.scaled;	
			
		USviewerWidget->getTheUSImageLabel()->setScaledContents(true);
		USviewerWidget->getTheUSImageLabel()->setPixmap(pixmapUS);
			
		QString liveFile = i->getLiveFile();
		std::cout<<"Displaying the Live image .." <<qPrintable(liveFile);
		QPixmap pixmapLive(liveFile);
		USviewerWidget->getTheLiveImageLabel()->setScaledContents(true);
		USviewerWidget->getTheLiveImageLabel()->setPixmap(pixmapLive);

		}
	}

}

// 0 is US tab
// 1 
void LapUSMainWindow::tabChanged(int v){


    std::cout<<"\n *** Tab Changed **** "  << v <<std::endl;
    // preop image widget active
    if(v == 0){
    	//videoWidget->show();
        preopViewerWidget->hide();
        USviewerWidget->show();
        justWidget->show();
    }
    if(v == 1){
        preopViewerWidget->show();
        USviewerWidget->hide();
        justWidget->hide();
    }
    // US image viewer active


}

void LapUSMainWindow::saveImages(){
	std::cout<<"Saving the images......\n";

	USimagewriter->Record(1);
	
	Liveimagewriter->Record(1);///////////////

	Sleep(50);
	// update the US browser tab
	this->browserWidget->updateUSBrowser();
}

LapUSMainWindow::~LapUSMainWindow(void)
{

}
void LapUSMainWindow::mouseClicked(int x , int y){

	std::cout<<"Resetting the released\n";
	std::cout<<"Setting the clicked \n";
	released = false;
	clicked = true;
	std::cout<<"Mouse clicked  x :"<< x << " y: " <<y <<std::endl;

	QMouseEvent* event = new QMouseEvent(QEvent::MouseButtonPress,QCursor::pos (),Qt::LeftButton,0,0);

	QRect widgetRect = Save->geometry();
	//QPoint mousePos = Save->mapFromGlobal(QCursor::pos());
	QPoint mousePos = QCursor::pos();
	if(widgetRect.contains(mousePos))
	{
		std::cout<<"Da Vinci pressing the save button \n";
		Save->animateClick();
	}

	QRect browserRect = browserWidget->geometry();
	if(browserRect.contains(mousePos)){
		std::cout<<"Da Vinci cliking on browser items\n";

	//	oldPos = mousePos;
	}

	QApplication::postEvent(this,event);
}
void LapUSMainWindow::mouseReleased(){
	released = true;
	clicked = false;

	std::cout<<"Resetting the clicked \n";
	std::cout<<"Setting the released \n";
	QMouseEvent* event = new QMouseEvent(QEvent::MouseButtonRelease,QCursor::pos (),Qt::LeftButton,0,0);

	QApplication::postEvent(this,event);

}
void LapUSMainWindow::mouseMoved(int x,int y){

	//std::cout<<"Mouse moved\n";
	QMouseEvent* event = new QMouseEvent(QEvent::MouseMove,QCursor::pos (),Qt::LeftButton,0,0);
	QPoint mousePos = QCursor::pos();

	QRect browserRect = browserWidget->geometry();
	if(browserRect.contains(mousePos)){
		//std::cout<<"Da Vinci moving in browser widget\n";
	

    QListWidgetItem* item = NULL, *oldItem = NULL;
	 if(browserWidget->currentIndex() == 0){

          //cout << "The scroll var value "<<browserWidget->list->verticalScrollBar()->value()<<"\n";

//         std::cout<<"Da vinci cursor moving in the US browser..\n";
         item = browserWidget->list->itemAt(browserWidget->mapFromGlobal(QCursor::pos()));
         oldItem = browserWidget->list->itemAt(browserWidget->mapFromGlobal(oldPos));


//         browserWidget->list->scrollToItem(item);
         // update only if the current item is not same as the old item TODO 
		 if(item && (item == oldItem)){
			// std::cout<<"Mouse still on the old item \n";
		 }
		 if(item && (item != oldItem)){
			std::cout<<"Mouse on a different item \n";

            std::cout<<"US Item found \n";
            this->showItem(item);

            browserWidget->list->setCurrentItem(item);
          }
            int dx = oldPos.x() - x;
            int dy = oldPos.y() -y ;
            if(clicked && !released){

            	int oldValue = browserWidget->list->verticalScrollBar()->value();
            	//cout << "The scroll var value "<<browserWidget->list->verticalScrollBar()->value()<<"\n";
				browserWidget->list->verticalScrollBar()->setValue(oldValue- (2 * dy));

			// 	browserWidget->list->scrollToItem(item,QAbstractItemView::PositionAtCenter);
        }
    }   
    else if(browserWidget->currentIndex() == 1){
        std::cout<<"Da vinci cursor moving in the preop browser..\n";
        item = browserWidget->list2->itemAt(browserWidget->mapFromGlobal(QCursor::pos()));  // change this TODO BAD programming 

        if(item){
            std::cout<<"Preop Item found \n";
            this->showItemPreop(item);
            browserWidget->list2->setCurrentItem(item);
            //Q_EMIT updatePreopImage(item);

 
        }

        //BAD  make API's in Browser widget
        int dx = oldPos.x() - x;
        int dy = oldPos.y() -y ;
        if(clicked && !released){

            	int oldValue = browserWidget->list2->verticalScrollBar()->value();
				browserWidget->list2->verticalScrollBar()->setValue(oldValue- (2 * dy));

			// 	browserWidget->list->scrollToItem(item,QAbstractItemView::PositionAtCenter);
        }
    }
}
		
	oldPos = QPoint(x,y);
	QApplication::postEvent(this,event);
}