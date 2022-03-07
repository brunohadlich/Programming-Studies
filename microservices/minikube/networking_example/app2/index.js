const process = require("process");
const express = require('express');
const axios = require('axios');

const api = axios.default.create({
	baseURL: `http://${process.env.API_HOST}:${process.env.API_PORT}`,
	timeout: 1000
})

const app = express();

app.get('/look_for_bar', async (req, res) => {
	res.send((await api.get('/bar')).data);
});

app.get('/look_for_foo', async (req, res) => {
	res.send((await api.get('/foo')).data);
});

app.listen(process.env.PORT, () => {
	console.log(`Running on port ${process.env.PORT}`);
});