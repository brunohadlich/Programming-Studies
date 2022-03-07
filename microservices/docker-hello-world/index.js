const express = require('express')
const port = 8000
const app = express()
const fs = require('fs');

app.get('/', (req, res) => {
	res.send("Hello world 2!");
});

app.get('/error', (req, res) => {
	process.exit(1);
});

app.get('/save_to_file', (req, res) => {
	fs.appendFileSync('/batata/xyz', req.query.foo);
	return res.send()
});

app.get('/read_from_file', (req, res) => {
	return res.send(fs.readFileSync('/batata/xyz').toString());
});

app.listen(port, () => {
	console.log(`Server up and running at localhost:${port}.`);
})