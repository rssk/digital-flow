const WebSocket = require('ws');
const { spawn } = require('child_process');

const wss = new WebSocket.Server({ port: 8789 });

wss.on('connection', (ws) => {
  const bmon = spawn(
		'bmon', ['-p', 'eth0', '-o', `format:fmt='$(attr:rxrate:bytes)\n'`],
	);
  bmon.stdout.on('data', (rxData) => {
    ws.send(rxData.toString().replace(/[']+/g, ''));
  });
  bmon.stderr.on('data', (err) => {
		console.error(`Command error: ${err}`);
  });
});
