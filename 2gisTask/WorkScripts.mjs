WorkerScript.onMessage = function(msg) {
    console.log(msg.action + ' ' + msg.word + ' ' + msg.num)
    var myModel = msg.model
    var word = msg.word
    var num = msg.num
    var oldWord = msg.oldWord


    if (msg.action === 'updateNumOfWord') {
        if(myModel.count === 0){
            myModel.append({word, num})
            myModel.sync();
            return
        }
        for(var i = 0; i < myModel.count; i++){
            var topElem = myModel.get(i)
            if(topElem.word === word){
                myModel.remove(i)
                myModel.append({word, num})
                myModel.sync();
                break
            }
            myModel.append({word, num})
        }
        myModel.sync();
        return
    }
    if (msg.action === 'changeTopElem') {
        for(i = 0; i < myModel.count; i++){
            topElem = myModel.get(i)
            if(topElem.word === oldWord){
                myModel.remove(i)
                myModel.append({word, num})
                break
            }
        }
        myModel.sync();
        return
    }
    if (msg.action === 'sortTop') {
        for(i = 0; i < myModel.count - 1; i++){
            topElem = myModel.get(i)
            for(var v = 0; v < myModel.count; v++){
                var topElemV = myModel.get(v)
                if(topElem.word < topElem.word){
                    var buf = topElemV;
                    topElemV = topElem;
                    topElem = buf;
                }
            }
        }
        myModel.sync();
        return
    }
}
