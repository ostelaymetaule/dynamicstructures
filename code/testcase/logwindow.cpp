#include "logwindow.h"
#include <QDateTime>

LogWindow::LogWindow(QWidget * parent)
:QTextEdit(parent)
{
    QString start= "<h2>debug window<h2>";
    this->setHtml(start);
}

void LogWindow::log(std::string&  msg,MsgType type)
{
    QString msgStr=QString(msg.c_str());
    log(msgStr,type);
}


void LogWindow::log(char* msg,MsgType type)
{
    QString msgStr=QString(msg);
    log(msgStr,type);

}

void LogWindow::log(QString  msg, MsgType type)
{
    QString br= "<br/>";

    this->setHtml(this->toHtml()+ "<div style='"+ getStyle(type) +"' >" + getTime()+  " - " + msg + "</div>" );
}
/*
void LogWindow::logToBuffer(QString  msg, MsgType type=normal_msg)
{
 QString br= "<br/>";
 mBufferedStr+= "<div style='"+ getStyle(type) +"' >" + getTime()+  " - " + msg + "</div>";

}
*/

void LogWindow::flush()
{

       this->setHtml(this->toHtml()+ mBufferedStr);
       mBufferedStr="";
}

 QString  LogWindow::getStyle(MsgType type)
 {
    QString style;

 switch(type)
 {
 case normal_msg:
    style="font-size:8pt;color:black";
     break;
 case succes_msg:
    style="font-size:10pt;font-weight:bold;color:rgb(150,255,150);";
     break;
 case failure_msg:
    style="font-size:10pt;font-weight:bold;color:rgb(255,0,0);";
     break;
 case important_msg:
    style="font-size:10pt;font-weight:bold;color:rgb(0,0,0);text-decoration:italic;";
    break;
 case very_important_msg:
    style="font-size:16pt;font-weight:bold;color:rgb(0,0,0);font-style:italic;";
    break;
  case sub_msg:
    style="margin-left:30px;font-size:8pt;font-weight:normal;color:rgb(150,150,150);";
    break;
 }

 return style;
 }


QString LogWindow::getTime()
{
   QTime time = QTime::currentTime();
   QString timeString = time.toString();

    return timeString;
}
