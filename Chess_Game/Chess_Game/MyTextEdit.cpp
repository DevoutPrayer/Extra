#include "widget.h"
#include <QKeyEvent>

/*MyTextEdit类继承了QTextEdit类，并重写keyPressEvent方法，
然后聊天的textEdit实例化为他的对象，就有了keyPressEvent的方法
当ENTER键按下的时候发送信号sendChatMeg(Qstring) ，
chatBrowser绑定该信号执行槽函数append()*/

MyTextEdit::MyTextEdit(QWidget *parent):QTextEdit(parent)
        {

//    w = (Widget *)parent;
}

void MyTextEdit::keyPressEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_Return){
        //截除开始和结尾处的空白字符，过去掉
        if(toPlainText().trimmed() == "")
            return;
        //把自己中的内容以信号的方式发送出去
       emit sendChatMsg(this->toPlainText());
//       toPlainText().toStdString().c_str();
//      将QString转换为const char *
       this->clear();
    }else{
        QTextEdit::keyPressEvent(e);
    }
}


