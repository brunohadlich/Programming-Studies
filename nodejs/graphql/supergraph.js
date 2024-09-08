const { ApolloServer } = require('apollo-server');
const { ApolloGateway, IntrospectAndCompose } = require('@apollo/gateway');

const gateway = new ApolloGateway({
	supergraphSdl: new IntrospectAndCompose({
		subgraphs: [
			{ name: 'library', url: 'http://localhost:4001/' },
			{ name: 'user', url: 'http://localhost:4002/' }
		]
	})
});

const server = new ApolloServer({ gateway, introspection: true });

server.listen({port: 4000}).then(({ url }) => {
	console.log(`🚀 Gateway ready at ${url}`);
}).catch((err) => {
	console.error(err);
});