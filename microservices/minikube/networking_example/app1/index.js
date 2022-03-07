const process = require("process");
const express = require('express');
const os = require("os");

const app = express();

app.get('/bar', async (req, res) => {
	res.send(`'/bar' from ${os.hostname()}`);
});

app.get('/foo', async (req, res) => {
	res.send(`'/foo' from ${os.hostname()}`);
});

app.listen(process.env.PORT, () => {
	console.log(`Running on port ${process.env.PORT}`);
});