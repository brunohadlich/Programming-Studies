const {getArray, validateArguments} = require('./pagination')

test('getArray(1, 10)', () => {
	expect(getArray(1, 10)).toEqual(['**1**', '2', '3', '4', '5', '...']);
})

test('getArray(2, 10)', () => {
	expect(getArray(2, 10)).toEqual(['1', '**2**', '3', '4', '5', '...']);
})

test('getArray(3, 10)', () => {
	expect(getArray(3, 10)).toEqual(['1', '2', '**3**', '4', '5', '...']);
})

test('getArray(4, 10)', () => {
	expect(getArray(4, 10)).toEqual(['...', '2', '3', '**4**', '5', '6', '...']);
})

test('getArray(5, 10)', () => {
	expect(getArray(5, 10)).toEqual(['...', '3', '4', '**5**', '6', '7', '...']);
})

test('getArray(6, 10)', () => {
	expect(getArray(6, 10)).toEqual(['...', '4', '5', '**6**', '7', '8', '...']);
})

test('getArray(7, 10)', () => {
	expect(getArray(7, 10)).toEqual(['...', '5', '6', '**7**', '8', '9', '...']);
})

test('getArray(8, 10)', () => {
	expect(getArray(8, 10)).toEqual(['...', '6', '7', '**8**', '9', '10']);
})

test('getArray(9, 10)', () => {
	expect(getArray(9, 10)).toEqual(['...', '6', '7', '8', '**9**', '10']);
})

test('getArray(10, 10)', () => {
	expect(getArray(10, 10)).toEqual(['...', '6', '7', '8', '9', '**10**']);
})

test('validateArguments(10,10)', () => {
	expect(validateArguments(10, 10)).toEqual(false);
})

test('validateArguments("asd",10)', () => {
	expect(validateArguments("asd", 10)).toEqual("Requisição mal formada. Esperava o formato '/paginacao?paginaAtual={X}&quantidadePaginas={Y}' onde {X} e {Y} são números inteiros maiores ou igual a 1.");
})

test('validateArguments(10,"asd")', () => {
	expect(validateArguments(10, "asd")).toEqual("Requisição mal formada. Esperava o formato '/paginacao?paginaAtual={X}&quantidadePaginas={Y}' onde {X} e {Y} são números inteiros maiores ou igual a 1.");
})

test('validateArguments(undefined,undefined)', () => {
	expect(validateArguments(undefined, undefined)).toEqual("Requisição mal formada. Esperava o formato '/paginacao?paginaAtual={X}&quantidadePaginas={Y}' onde {X} e {Y} são números inteiros maiores ou igual a 1.");
})

test('validateArguments(null,null)', () => {
	expect(validateArguments(null, null)).toEqual("Requisição mal formada. Esperava o formato '/paginacao?paginaAtual={X}&quantidadePaginas={Y}' onde {X} e {Y} são números inteiros maiores ou igual a 1.");
})

test('validateArguments(-1,10)', () => {
	expect(validateArguments(-1, 10)).toEqual('paginaAtual deve ser maior ou igual a 1.');
})

test('validateArguments(11,10)', () => {
	expect(validateArguments(11, 10)).toEqual('quantidadePaginas deve ser maior ou igual a paginaAtual.');
})