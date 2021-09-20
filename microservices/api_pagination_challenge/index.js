const express = require('express')
const { pagination } = require('./endpoints')
const port = 8000
const app = express()

const errorHandler = (err, req, res, next) => {
	if (err) {
		res.status(err.code).json({
			message: err.message
		});
	}
}

app.get('/paginacao', pagination);
app.use(errorHandler);

app.listen(port, () => {
	console.log(`Server up nd running at localhost:${port}.`);
})