const WebSocket = require('ws');

const ws = new WebSocket('ws://localhost:8789');

ws.on('open', () => {
  console.log('connected');
  ws.send('something');
});

ws.on('message', (data) => {
  console.log(data.toString());
});
