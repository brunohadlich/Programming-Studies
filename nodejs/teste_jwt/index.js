const jwt = require('jsonwebtoken');
const fs = require('fs');

const toEncode = "a pretty nice message";
const expiresInSeconds = 5;

const token = jwt.sign({data: toEncode, exp: Math.floor(Date.now() / 1000) + expiresInSeconds}, fs.readFileSync('./private-key.pem'), {algorithm: 'RS256'});

console.log(`Generated token: ${token}`);

try {
	const decoded = jwt.verify(token, fs.readFileSync('public-key.pem'));
	console.log("The token is valid");
	console.log(`Token: ${JSON.stringify(decoded)}`);
} catch(err) {
	console.log("The token is NOT valid");
	const decoded = jwt.decode(token);
	console.log(`Token: ${JSON.stringify(decoded)}`);
}