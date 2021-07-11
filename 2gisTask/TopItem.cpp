#include "TopItem.h"


TopItem::TopItem(QObject *parent) : QObject(parent)
{

}


QString TopItem::word() const{
  return _word;
}

void TopItem::setWord(const QString & w){
  _word = w;
}

int TopItem::num() const{
  return _num;
}

void TopItem::setNum(int n){
  _num = n;
}
