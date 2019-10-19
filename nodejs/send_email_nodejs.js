var nodemailer = require('nodemailer');

var transport = nodemailer.createTransport({
	host: "smtp-mail.outlook.com", // hostname
	secureConnection: false, // TLS requires secureConnection to be false
	port: 587, // port for secure SMTP
	auth: {
		user: "email@hotmail.com",
		pass: "password"
	},
	tls: {
		ciphers:'SSLv3'
	}
});

var mailOptions = {
	to: 'email@gmail.com', // list of receivers
	subject: 'Hello ✔', // Subject line
	text: 'Hello world?', // plain text body
	html: '<b>Hello world?</b>' // html body
};

function mail_handler(error, info) {
	if (error)
		return console.log(error);

	console.log('Message sent: %s', info.messageId);
	console.log('Preview URL: %s', nodemailer.getTestMessageUrl(info));
}

transport.sendMail(mailOptions, mail_handler);
