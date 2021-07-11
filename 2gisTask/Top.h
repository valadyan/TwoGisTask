#ifndef TOP_H
#define TOP_H

#include <QObject>
#include <QThread>
#include <QMap>
#include <QString>

#include <QDebug>

class Top : public QObject
{
  Q_OBJECT

  QMap<QString, int8_t> _topMap{{"",0}};
  QMap<QString, int8_t> _cacheMap;
  int8_t _topSize = 15;
  int8_t _minTopElem = 1;

public slots:
  void addWord(const QString& word);

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
signals:
  void addWordInTop(const QString& );
  void changedNum(QString word, int num);
  void changedTopElem(QString oldWord, QString word , int num);
  void endOfFile();
};

#endif // TOP_H
