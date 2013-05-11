#include "LapUSMouse.h"

LapUSMouse::LapUSMouse(void){

	// TODO probabaly we do not need to create the davinci outside lets see
	//this->parent = parent;

 //    this->setAttribute(Qt::WA_AcceptTouchEvents);  
 //    this->setAttribute(Qt::WA_MouseTracking);

	// std::cout<<"Creating the LapUSMouse\n";

	// QDesktopWidget *desk = QApplication::desktop();
	// if(desk)
 //    	screenSize = desk->screenGeometry(0);
	//cursor = new QCursor();

}
LapUSMouse::LapUSMouse(mtsIntuitiveDaVinci *daVinci ,QWidget* mainWidget) {

//	this->parent = parent;	
	this->daVinci = daVinci;
	this->mainWidget = mainWidget;
	setAutoFillBackground(true);
	setScaledContents(true);
	resize(50,50);
	setText("I am a mouse");


	//setPixmap(Qt::red);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);	

	setupDaVinci(); 
	//update the first time 
	updateDaVinci();
	QDesktopWidget *desk = QApplication::desktop();
	if(desk)
    	screenSize = desk->screenGeometry(0);

    std::cout<<"Screen size width "<<screenSize.width()<<std::endl;
    std::cout<<"Screen size height "<<screenSize.height()<<std::endl;

	// connect with the timer to update the mouse position every 50 milliseconds
	connect( &timer, SIGNAL(timeout()), this, SLOT(updateMouse()) );
    timer.start( 100 );
    
}

void LapUSMouse::setupDaVinci(void){

	MTMR1_Interface = daVinci->GetInterfaceProvided("MTMR1");
	if (!MTMR1_Interface) {
		CMN_LOG_INIT_ERROR << "Could not find daVinci MTMR1" << std::endl;
		std::cout<<"Could not find the daVinci MTMR\n";
	}
	else{

		std::cout<<"Found the MTMR interface \n";
	}

	GetPositionTipMTMR1.Bind(MTMR1_Interface->GetCommandRead("GetPositionCartesian"));

	    if (callbacks.AddHandlers(daVinci)) {
		    std::cout << "Callbacks initiated" << std::endl;
	    } else {
		   std::cout << "Callback init error!" << std::endl;
	    }
	return;
}

void LapUSMouse::updateDaVinci(void ){
	if (daVinci->IsAPIConnected()) {
		GetPositionTipMTMR1(arm_right);

		// getting the x and the y positions 
		//int x = arm_right.Position().Translation()[0];
		//int y = arm_right.Position().Translation()[1];

		//std::cout<<"x Position of the mouse " <<x <<std::endl;
		//std::cout<<"y position of the mouse " <<y <<std::endl;	
	}
	return;
}
// void LapUSMouse::pinched(){
// 	// now check the position of the cursor 
// 	// if it lies inside the save button then save


// }

// this is called every 50 seconds to get the position of the daVinci arm
void LapUSMouse::updateMouse(void ){
//	std::cout<<"Updating the mouse \n";
//	if  (!callbacks.headOut && callbacks.headOutState && callbacks.footOn){

	std::cout<<"mamRight "<<callbacks.mamRight <<"mamLeft" <<callbacks.mamLeft <<"mamFoot On"<<callbacks.mamFootOn <<std::endl;
	if(callbacks.mamRight && callbacks.mamLeft && callbacks.mamFootOn){
		//std::cout<<"Inside that state \n";
		// update the qlabel position 
		int x = arm_right.Position().Translation()[0];
		int y = arm_right.Position().Translation()[1];		

		//std::cout<<"position of the arm x :" <<x <<" y: "<<y;
		
		// TODO check for the best projection
		unsigned int pos_x, pos_y;

		pos_x = screenSize.width()/4 - x*4;
		pos_y = screenSize.height() - y*10;

		if (pos_x < 0 ){
			pos_x = 0;
		}
	// 	if(pos_x > screenSize){
	// 		pos_x = (unsigned int)screenSize.width();
	// 	}
	// //	QCustomEvent *customevent = new QCustomEvent
//		this->move(pos_x,pos_y);
//		this->show();  
		cursor.setPos(pos_x, pos_y);

		// QMouseEvent* event = new QMouseEvent(QEvent::MouseMove,QCursor::pos (),Qt::NoButton,0,0);
		// QApplication::postEvent(mainWidget,event);

		Q_EMIT moved(pos_x,pos_y);
		
		if (callbacks.rightButton){

			// Here create a new QT signal or event that will create 
			std::cout<<"Right button clicked \n";
			callbacks.rightButton = false;
			Q_EMIT pinched(pos_x,pos_y);
		}
		if(callbacks.released){

			callbacks.released = false;
			Q_EMIT released();
		}

//		cursor.setPos(pos_x, pos_y);
//	}


	// update the arm position 
	updateDaVinci();

	}
	return ;
}

//  bool LapUSMouse::event(QEvent *event)
// {   
// 	std::cout<<"Got the event \n";
// 	if(!event){
// 		std::cout<<"I am an empty event :D";
// 		return false;
// 	}
// 	std::cout<<"Trying to access the event \n";
// 	std::cout<<event->type();
//   //  return true;
//     switch (event->type()) {
//         case QEvent::TouchBegin:
//         {
//          	std::cout<<"My event yeee \n";
// 			QPointF pos = static_cast<QTouchEvent*>(event)->touchPoints().first().pos();
// 			unsigned int pos_x, pos_y;
// 			pos_x = screenSize.width()/4 - (pos.x())*4;
// 			pos_y = screenSize.height() - (pos.y())*10;

// 			if  (!callbacks.headOut && callbacks.headOutState && callbacks.footOn)
// 			{ 
// 				QCursor::setPos(pos_x, pos_y);

// 				if (callbacks.rightButton)
// 				{
// 						// Change mouse color temporarily
// //						QApplication::setOverrideCursor(*mouseShapeDarkRed);

// 						// Evoke mouse event
// 					//	mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, pos_x, pos_y, pos_x, pos_y);

// 						// Pause system to prevent multiple triggers
// 					//	osaSleep(0.6);
// 						callbacks.rightButton = false;  
// 				}
// 			}
// 			 break;
//         }	
//         default: {
//         std::cout<<"Default";
//     	}	
//     }
// 	std::cout<<"Accepting the event \n";
//     event->accept();
// 	std::cout<<"Event accepted  \n";
//     return true;
// }
LapUSMouse::~LapUSMouse(void){
	std::cout<<"Lap Us destrucrs \n";}
	