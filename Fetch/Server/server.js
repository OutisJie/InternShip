var http = require("http");
var hostname = "localhost";
var port = 3001;

var server = http.createServer(function(req, res){
    res.setHeader('Content-Type', 'text/plan');
    res.end('Good day');
});

server.listen(port, hostname, function(){
    console.log('user connected');
});