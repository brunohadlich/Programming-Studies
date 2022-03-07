const express = require("express");
const app = express()
const PORT = 3000;

//will run for:	http://localhost:3000/foo
//also for:		http://localhost:3000/foo/bar
app.use('/foo', (req, res, next) => {
	console.log('foo 1');
	next();
});

app.use('/bar', (req, res, next) => {
	console.log('bar 1');
	next();
});

app.use('/foo', (req, res, next) => {
	console.log('foo 2');
	next();
});

app.use('/baz', (req, res, next) => {
	console.log('baz 1');
	next();
}, (req, res, next) => {
	console.log('baz 2');
	next();
}, (req, res, next) => {
	console.log('baz 2');
	res.send();
});

//Without path middleware applies to any route
app.use((req, res, next) => {
	console.log('1');
	next();
});

//This middleware applies only to / route
app.use('/', (req, res, next) => {
	console.log('2');
	next();
});

//would enter only if the previous middleware placed
//an error as next() argument like next("myerror")
app.use((err, req, res, next) => {
	console.log('an error happened');
	next();
});

app.use((req, res, next) => {
	console.log('3');
	next("err");
});

app.use((err, req, res, next) => {
	const MSG = 'an error happened 2';
	console.log(MSG);
	next();
});

app.use('/', (req, res, next) => {
	console.log('4');
	res.send("4");
});

app.listen(PORT, () => {
	console.log(`running at port ${PORT}`);
});

//try running:
//	- localhost:3000/
//	- localhost:3000/foo
//	- localhost:3000/bar
//	- localhost:3000/baz