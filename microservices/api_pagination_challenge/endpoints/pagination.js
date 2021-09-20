const { v4: uuidv4 } = require('uuid');

function getArray(currPage, amountPages) {
	let result = [];
	if (amountPages <= 5) {
		//all pages fit into the array
		for (let i = 1; i < currPage; i++) {
			result.push(String(i));
		}
		result.push('**' + String(currPage) + '**')
		for (let i = currPage + 1; i <= amountPages; i++) {
			result.push(String(i));
		}
	} else {
		if (currPage > 3) {
			if (amountPages - currPage > 2 ) {
				//array starts with ... and ends with ...
				result.push('...');
				for (let i = currPage - 2; i < currPage; i++) {
					result.push(String(i));
				}
				result.push('**' + String(currPage) + '**')
				for (let i = currPage + 1; i <= currPage + 2; i++) {
					result.push(String(i));
				}
				result.push('...');
			} else {
				//array starts with ... and ends with a number
				result.push('...');
				for (let i = amountPages - 4; i < currPage; i++) {
					result.push(String(i));
				}
				result.push('**' + String(currPage) + '**');
				for (let i = currPage + 1; i <= amountPages; i++) {
					result.push(String(i));
				}
			}
		} else {
			//array starts with a number and ends with ...
			for (let i = 1; i < currPage; i++) {
				result.push(String(i));
			}
			result.push('**' + String(currPage) + '**');
			for (let i = currPage + 1; i <= 5; i++) {
				result.push(String(i));
			}
			result.push('...');
		}
	}
	return result;
}

function validateArguments(currPage, amountPages) {
	if (!Number.isInteger(currPage) || !Number.isInteger(amountPages)) {
		return "Requisição mal formada. Esperava o formato '/paginacao?paginaAtual={X}&quantidadePaginas={Y}' onde {X} e {Y} são números inteiros maiores ou igual a 1.";
	} else if (currPage < 1) {
		return 'paginaAtual deve ser maior ou igual a 1.';
	} else if (amountPages < currPage) {
		return 'quantidadePaginas deve ser maior ou igual a paginaAtual.';
	}
	return false;
}

function pagination(req, res, next) {
	const currPage = Number.parseInt(req.query.paginaAtual);
	const amountPages = Number.parseInt(req.query.quantidadePaginas);
	const error =  validateArguments(currPage, amountPages);
	if (error) {
		next({
			code: 400,
			message: error
		});
	} else {
		res.json([{id: uuidv4(), paginacao: getArray(currPage, amountPages)}]);
	}
}

module.exports.validateArguments = validateArguments;
module.exports.getArray = getArray;
module.exports.pagination = pagination;