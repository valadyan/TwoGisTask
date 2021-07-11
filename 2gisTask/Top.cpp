#include "Top.h"

void Top::addWord(const QString& word) {
  if(_topMap.contains(word) || _topMap.size() <= _topSize){
    auto num = ++_topMap[word];
    emit updatedNum(word, num);
    return ;
  }
  int8_t num = ++_cacheMap[word];
  if(_minTopElem < num){
      QString minTopWord = _topMap.key(_minTopElem);
      _cacheMap[minTopWord] = _minTopElem;
      _topMap.erase(_topMap.find(minTopWord));
      _topMap[word] = num;

      emit updatedTopElem(minTopWord, word, num);

      for(auto& n: _topMap.values())
          if(_minTopElem > n && n >= 1)
            _minTopElem = n;
  }

}
