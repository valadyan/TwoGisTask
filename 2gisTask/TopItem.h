#ifndef TOPITEM_H
#define TOPITEM_H

#include <QObject>
#include <QString>


class TopItem : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString word READ word WRITE setWord)
  Q_PROPERTY(int num READ num WRITE setNum)
public:
  explicit TopItem(QObject *parent = nullptr);

  QString word() const;
  void setWord(const QString &);

  int num() const;
  void setNum(int);

  private:
  QString _word;
  int _num;

};
//Q_DECLARE_METATYPE(TopItem)

#endif // TOPITEM_H
