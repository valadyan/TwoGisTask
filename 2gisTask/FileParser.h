#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QObject>
#include <QFile>
#include <QMap>
#include <QTextStream>


class FileParser: public QObject
{
  Q_OBJECT

//  QMap<QString, int8_t> wordsMap;
  QFile* _file;
public:
  FileParser(QFile* file);
  void readFile();
signals:
  void sendWord(const QString& word);
  void eof();
};

#endif // FILEPARSER_H
