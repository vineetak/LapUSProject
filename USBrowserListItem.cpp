#include "USBrowserListItem.h"
#include <iostream>

USBrowserListItem::USBrowserListItem(void)
{


}
USBrowserListItem::USBrowserListItem(QString US,QString Live)
{
	LiveFile = Live;
	USFile = US;
	icon = QIcon(US);
	setIcon(icon);
	QPixmap base(US);
	QPixmap overlay(Live);
	//QPixmap base, overlay; // come from your code
	QPixmap result(base.width(), base.height());
	//result.fill(Qt::Transparent); // force alpha channel
	//{
		QPainter painter(&result);
		painter.drawPixmap(0, 0, base);
		painter.drawPixmap(20, 20, overlay);
	//}*/
//	QPainter painter;
	//painter.begin(&base);
    //painter.drawPixmap(30, 30, overlay);
	icon.addPixmap(base);
}
USBrowserListItem::~USBrowserListItem(void){}


QString USBrowserListItem::getLiveFile(){
	return LiveFile;
}
QString USBrowserListItem::getUSFile(){
	return USFile;
}
