const express = require('express');
const app = express();
const port = 2306;

app.use((req, res, next) => {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE, OPTIONS');
    res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept');
    next();
});

app.get('/hi', hi);
app.listen(port, startServer);

function hi(req, res){
    res.send('안녕하세요 와 또 안되면 교수님께 연락드릴려 했는데 안해도 되겠다 ㅎㅎ');
    // 근데 이게 맞나 
}

function startServer(){
    console.log('살려줘 이 각박한 현실 속에서 http://localhost:${port}/hi');
}