#include "BrowserWidget.h"
#include <iostream>

BrowserWidget::BrowserWidget(void)
{
}

BrowserWidget::BrowserWidget(QWidget* parent)
{
    QString tabBarStyle = "QTabBar::tab{height:40px; width:108px; font: 11pt; font-weight: bold;}";

    setMouseTracking(true);
    tabBar()->setMouseTracking(true);   

    setMouseTracking(true);

	std::cout<<"Creating the browser widget......\n";
	// QTabWidget* bottom = new QTabWidget;
    //QScrollBar * b = new QScrollBar();
	this->setParent(parent);
	//this->setTabsClosable(true);
    this->setMovable(true);
    this->setStyleSheet(tabBarStyle);

  //  scroller = new QsKineticScroller(this);

    /* ------- US image browser tab ---------- */
  //  list = new QListWidget();
	list = new USBrowserList();
	list->setViewMode(QListView::IconMode);
    list->setIconSize(QSize(200,200));
    list->setMouseTracking(true);
    //list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //list->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
//    scroller->enableKineticScrollFor(list);

//    QString sPath = "C://Users//Public//Pictures//Sample Pictures";
    //  QDir dir("C:\Users\Public\Pictures");
	QString sPath = "./SaveFolder";
    QDir dir(sPath);
    std::cout <<"The directory exists = "<<dir.exists();

    /* Get all the Live_ files in sorted order*/
    QStringList filters;
    filters << "Live_*.bmp" ;
	//filters<<"Live_";
    dir.setNameFilters(filters);
	dir.setSorting(QDir::Time);
    QFileInfoList listLive = dir.entryInfoList();

	std::list<QString> liveFileList;

   // std::cout << "Finding the live files........" << std::endl;
    for (int i = 0; i < listLive.size(); ++i) {
	//	std::cout<<"Found live file \n";
        QFileInfo fileInfo = listLive.at(i);
		/*QDateTime d = fileInfo.created();
		QDateTime d1 = fileInfo.lastModified();
		QString *str = new QString();
		*str = d.toString("dd/MM/yyyy hh:mm:ss");
		std::cout<<"Creation date  : " <<qPrintable((*str)) ;
		QString lastModified = d1.toString("dd/MM/yyyy hh:mm:ss");
		std::cout<<" Modification time  : " <<qPrintable(lastModified) <<std::endl;
        std::cout<< qPrintable(QString("%1 %2").arg(fileInfo.fileName()));
		*/

		liveFileList.push_back(fileInfo.absoluteFilePath());
	//	std::cout<< qPrintable(fileInfo.absoluteFilePath()) <<std::endl;
//        QListWidgetItem *item1 = new QListWidgetItem(QIcon(fileInfo.absoluteFilePath()), "L1", list);
//        list->insertItem(i, item1);
//		list->setBaseSize(100,100);
    }

    /* Get all the US_ files sorted by */
    QStringList filterUS;
    filterUS << "US_*.bmp" ;
	dir.setNameFilters(filterUS);
	dir.setSorting(QDir::Time);
    QFileInfoList listUS = dir.entryInfoList();

	std::list<QString> USFileList;

    std::cout << "Finding the US files....." << std::endl;
    for (int i = 0; i < listUS.size(); ++i) {
		std::cout<<"Found US file :";
		QFileInfo fileInfo = listUS.at(i);
		USFileList.push_back(fileInfo.absoluteFilePath());
	//	std::cout<< qPrintable(fileInfo.absoluteFilePath()) <<std::endl;
    }

	/* Create the USBrowserList Items */
    std::list<QString>::iterator it = liveFileList.begin();
    std::list<QString>::iterator itUS = USFileList.begin();
    
	int count = 0;
    for (it ; it != liveFileList.end(); it++){
        USBrowserListItem *item = new USBrowserListItem(*(itUS),*(it));
		list->insertItem(count,item);
		list->setBaseSize(100,100);
		count++;
        itUS++;
    }
	
    connect(list, SIGNAL(itemClicked(QListWidgetItem *)),this->parentWidget(), SLOT(showItem    (QListWidgetItem *)));
    //connect(list, SIGNAL(itemClicked(QListWidgetItem *)),this, SLOT(Scroll()));
    //connect(list, SIGNAL(USitemClicked(USBrowserListItem *)),this->parentWidget(), SLOT(showItem    (USBrowserListItem *)));

    /* ------- Preop image browser tab --------- */
    list2 = new QListWidget();
    list2->setViewMode(QListView::IconMode);
    list2->setIconSize(QSize(200,200));
    list2->setMouseTracking(true);
 //   list2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    list2->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);

    //QString sPath2 = "C://Users//Public//Pictures//Sample Pictures";
	QString sPath2 = "C://Users//Vineeta-Admin//CIS-Project//build//Release//Preop";
    //  QDir dir("C:\Users\Public\Pictures");
    QDir dir2(sPath2);
    std::cout <<"The directoty exists = "<<dir2.exists();
    QStringList filters2;
    filters2 << "*.jpg" ;
    dir2.setNameFilters(filters2);

    QFileInfoList list3 = dir2.entryInfoList();

    std::cout << "     Bytes Filename" << std::endl;
    for (int i = 0; i < list3.size(); ++i) {
        QFileInfo fileInfo = list3.at(i);
        std::cout<< qPrintable(QString("%1 %2").arg(fileInfo.fileName()));
        QListWidgetItem *item1 = new QListWidgetItem(QIcon(fileInfo.absoluteFilePath()),""  ,list2);
        list2->insertItem(i, item1);
        list2->setBaseSize(200,200);

    }
	//this->parentWidget();
    connect(list2, SIGNAL(itemClicked(QListWidgetItem *)),this->parentWidget(), SLOT(showItemPreop    (QListWidgetItem *)));

    /* ----- Add the tabs to the tab widget ------- */
    this->addTab(list,tr("Ultrasound"));
    this->addTab(list2,tr("Preoperative"));
    connect(this,SIGNAL(currentChanged(int)),this->parentWidget(),SLOT(tabChanged(int)));

}

void BrowserWidget::updateUSBrowser(){

	/*Get the last modified US file in the save folder */
    QStringList filterUS;
    filterUS << "US_*.bmp" ;

    QDir d("./SaveFolder"); // TODO make it configurable
    QString us = LapUSUtil::getTheLastModifiedFile(d,filterUS);

	/*Get the last modofied Live file in the save folder */
    QStringList filterLive;
    filterLive << "Live_*.bmp" ;

//    QDir d("./SaveFolder"); // TODO make it configurable
    QString live = LapUSUtil::getTheLastModifiedFile(d,filterLive);

	std::cout<<"The last modified live file was " <<qPrintable(live)<<std::endl;
	std::cout<<"The last modified us file was " <<qPrintable(us)<<std::endl;
	/* Create new USBrowser list item */
    USBrowserListItem *item = new USBrowserListItem(us,live);

    int insertAt = list->count() + 1;
    list->insertItem(insertAt, item);

	/*  not sure update the widget */

	// TODO see if we need to show the latest item

}


/*

BrowserWidget::updateUSWidget(){
		
		QListWidgetItem *item1 = new QListWidgetItem(QIcon(fileInfo.absoluteFilePath()), "L1", list2);
        list2->insertItem(i, item1);
        list2->setBaseSize(100,100);
		
}*/
BrowserWidget::~BrowserWidget(void)
{
}

void BrowserWidget::mouseMoveEvent ( QMouseEvent * event )
{
    std::cout<<"Mouse moving in the browser ... ,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,\n";
    QTabBar *wid = tabBar();
    if (wid && wid->tabAt(event->pos()) != -1){
        std::cout<<"Moving over the tab widget \n";
        //setTabEnabled(wid->tabAt(event->pos()),true); 
        this->setCurrentIndex(wid->tabAt(event->pos()));
        Q_EMIT currentChanged(wid->tabAt(event->pos())) ;  

    }

 //    QListWidgetItem* item = NULL;
	// if(currentIndex() == 0){

 //        std::cout<<"Da vinci cursor moving in the US browser..\n";
 //        item = list->itemAt((QCursor::pos()));
 //        // update only if the current item is not same as the old item TODO 
 //        if(item){
 //            std::cout<<"US Item found \n";
 //            Q_EMIT updateUSImage(item);

 //        }
 //    }   
 //    else if(currentIndex() == 1){
 //        std::cout<<"Da vinci cursor moving in the preop browser..\n";
 //        item = list2->itemAt(mapFromGlobal(QCursor::pos()));
 //        if(item){
 //            std::cout<<"Preop Item found \n";
 //            Q_EMIT updatePreopImage(item);

 
 //        }
 //    }

 //     qDebug() << "mouse hovering in tab " << wid->tabAt(event->pos());
    return QTabWidget::mouseMoveEvent(event);
  }

// void BrowserWidget::Scroll(){

//     std::cout<<"Scrolling the BrowserWidget\n";
//     //QListWidgetItem* currentItem;
//     int current;
//     if(currentIndex() == 0){
//         current = list->currentRow();
//         std::cout<<"The current row is "<<current <<std::endl;
//         //list->setCurrentItem(list->scrollTo(current+1));
//       //  list->setCurrentItem(list->item(current+1));
// 	//	list->setCurrentRow(current + 1);
// 		//list->scrollToItem(list->item(current+4));
        
//  //       if(current = list->count())
//    //         list->setCurrentRow(0) ;
//     //    else
//       //      list->setCurrentRow(current+1) ; 
//     }
//     else{
//         current = list2->currentRow();
//         if(current = list2->count())
//             list2->setCurrentRow(0) ;
//         else
//             list2->setCurrentRow(current+1) ;
//     }

// }