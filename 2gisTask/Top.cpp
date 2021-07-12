#include "Top.h"

void Top::addWord(const QString& word) {
  if(_topMap.size() < _topSize){
      auto num = ++_topMap[word];
      emit updatedNum(word, num);
      return ;
  }
  if(_topMap.contains(word)){
    auto num = ++_topMap[word];
    emit updatedNum(word, num);
    return ;
  }
  int8_t num = ++_cacheMap[word];
  if(_minTopElem < num){
      QString minTopWord = _topMap.key(_minTopElem);
      if(!minTopWord.isEmpty()){
        _cacheMap[minTopWord] = _minTopElem;
        _topMap.remove(minTopWord);
        _topMap[word] = num;
      }

      emit updatedTopElem(minTopWord, word, num);

      _minTopElem = _topMap.begin().value();
      for(auto& n: _topMap.values())
          if(_minTopElem > n && n >= 1)
            _minTopElem = n;
  }

}
