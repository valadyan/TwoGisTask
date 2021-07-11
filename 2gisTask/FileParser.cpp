#include "FileParser.h"
#include <QDebug>

FileParser::FileParser(QFile* file)
{
  _file = file;
//  QString word;
//  QTextStream in(_file);
//  while(!in.atEnd()){
//    in >> word;
//    emit sendWord(word);
////    auto num = wordsMap[word];
////    wordsMap[word] = ++num;
//  }
//  qDebug() << "done reading";
//  emit eof();
//  auto sortList = wordsMap.values().toStdList();
//  sortList.sort();
//  sortList.unique();
//  sortList.reverse();
//  int count = 0;
//  for(auto it = sortList.begin(); count < 15 && it != sortList.end(); it++, count++){
//      auto words = wordsMap.keys(*it);
//      for(auto wordIt = words.begin(); wordIt != words.end() && count < 15; count++, wordIt++){
//          qDebug() << *wordIt << "[" << *it << "]" << endl;
//        }
//  }
}

void FileParser::readFile(){
  QString word;
  QTextStream in(_file);
  while(!in.atEnd()){
    in >> word;
    emit sendWord(word);
//    auto num = wordsMap[word];
//    wordsMap[word] = ++num;
  }
  emit eof();
}
