const http = require('http');
const port = process.env.PORT || 8080;
let version = process.env.DVRVERSION || 'VERSION';

const requestListener = function (req, res) {
  res.writeHead(200);
  res.end(version);
}

const server = http.createServer(requestListener);
console.log("Starting server on port " + port + "\nWith version: " + version);
server.listen(port);