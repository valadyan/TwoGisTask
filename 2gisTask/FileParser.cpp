#include "FileParser.h"
#include <QDebug>

FileParser::FileParser(QFile* file)
{
  _file = file;
}

void FileParser::readFile(){
  QString word;
  QTextStream in(_file);
  while(!in.atEnd()){
    in >> word;
    if(word.isEmpty())
       continue;
    emit sendWord(word);
  }
  emit eof();
}
