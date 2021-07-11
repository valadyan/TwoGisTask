#ifndef TOP_H
#define TOP_H

#include <QObject>
#include <QThread>
#include <QMap>
#include <QString>
#include <QPair>
#include "TopItem.h"

#include <QDebug>

class Top : public QObject
{
  Q_OBJECT

  QMap<QString, int8_t> _topMap{{"",0}};
  QMap<QString, int8_t> _cacheMap;
  int8_t _topSize = 15;
  int8_t _minTopElem = 1;

public:
  Top();
public slots:
  void addWord(const QString& word) {
    if(_topMap.contains(word) || _topMap.size() < _topSize){
      auto num = ++_topMap[word];
      emit updatedNum(word, num);
      return ;
    }
    int8_t num = ++_cacheMap[word];
    if(_minTopElem < num){
        QString minTopWord = _topMap.key(_minTopElem);
        _cacheMap[minTopWord] = _minTopElem;
        _topMap.erase(_topMap.find(_topMap.key(_minTopElem)));
        _topMap[word] = num;

        qDebug()<<word<<"111";
        emit updatedTopElem(_topMap.key(_minTopElem), word, num);

        for(auto& n: _topMap.values())
            if(_minTopElem > n)
              _minTopElem = n;
    }

  }

signals:
  void updatedNum(QString, int);
  void updatedTopElem(QString, QString, int);
};

class TopController : public QObject
{
  Q_OBJECT
  QThread topThread;
  Top *top;
public:
  TopController() {
      top = new Top;
      top->moveToThread(&topThread);
      initConnections();
      topThread.start();
  }
  void initConnections(){
    connect(&topThread, &QThread::finished, top, &QObject::deleteLater);
    connect(this, &TopController::addWordInTop, top, &Top::addWord);
    connect(top, &Top::updatedNum, this, &TopController::changedNum);
    connect(top, &Top::updatedTopElem, this, &TopController::changedTopElem);
  }
  ~TopController() {
      topThread.quit();
      topThread.wait();
  }
public slots:
signals:
  void addWordInTop(const QString& );
  void topUpdated();
  void changedNum(QString word, int num);
  void changedTopElem(QString oldWord, QString word , int num);
  void endOfFile();
};

#endif // TOP_H
