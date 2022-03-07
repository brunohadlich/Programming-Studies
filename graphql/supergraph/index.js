const { ApolloServer } = require('apollo-server');
const { ApolloGateway } = require('@apollo/gateway');
const fs = require('fs');

const supergraphSdl = fs.readFileSync('./supergraph-schema.graphql').toString();

const gateway = new ApolloGateway({ supergraphSdl });

const server = new ApolloServer({ gateway });

server.listen({port: 4000}).then(({ url }) => {
	console.log(`🚀 Gateway ready at ${url}`);
}).catch((err) => {
	console.error(err);
});