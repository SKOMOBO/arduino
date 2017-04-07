//Lets require/import the HTTP module
var http = require('http');
var mysql = require('mysql2');

//Lets define a port we want to listen to
const PORT=8080; 


//We need a function which handles requests and send response


// create the connection to database
var connection = mysql.createConnection({host:'localhost', user: 'root', database: 'skomobo', password: 'dev1234'});

// simple query
connection.query('SELECT * FROM `sensor_data`', function (err, results, fields) {
  console.log(results); // results contains rows returned by server
  console.log(fields); // fields contains extra meta data about results, if available
});

function handleRequest(request, response){
    
    if(request.url != '/favicon.ico'){

        var text = request.url.split('-').join(' ').slice(1)        
        // io.appendFile('log.txt', text + '\n', (err) =>{
        //     if(err) console.log(err)
        // })

    }

}

//Create a server
var server = http.createServer(handleRequest);

//Lets start our server
server.listen(PORT, function(){
    //Callback triggered when server is successfully listening. Hurray!
    console.log("Server listening on: http://localhost:%s", PORT);
});
