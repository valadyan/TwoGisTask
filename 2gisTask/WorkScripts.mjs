WorkerScript.onMessage = function(msg) {
    console.log(msg.action + ' ' + msg.word + ' ' + msg.num + ' ' + msg.model.count + msg.oldWord)
    var myModel = msg.model
    var word = msg.word
    var num = msg.num
    var oldWord = msg.oldWord
    let topElem

    if (msg.action === 'updateNumOfWord') {
        WorkerScript.sendMessage({'maxNum': msg.num})
        if(myModel.count === 0){
            myModel.append({word, num})
            myModel.sync();
            return
        }
        for(var i = 0; i < myModel.count; i++){
            topElem = myModel.get(i)
            if(topElem.word === word){
                myModel.set(i, {word, num})
                myModel.sync();
                return
            }
        }
        myModel.append({word, num})
        myModel.sync();
        return
    }
    if (msg.action === 'changeTopElem') {
        for(i = 0; i < myModel.count; i++){
            topElem = myModel.get(i)
            if(topElem.word === oldWord){
                myModel.set(i, {word, num})
                myModel.sync();
                return
            }
        }
        console.log('000000000000')
    }
    if (msg.action === 'sortTop') {
        for(i = 0; i < myModel.count - 1; i++){
            topElem = myModel.get(i)
            for(var v = 0; v < myModel.count; v++){
                var topElemV = myModel.get(v)
                if(topElem.word < topElem.word){
                    //not now
                }
            }
        }
        myModel.sync();
        return
    }
}
