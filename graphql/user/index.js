const { ApolloServer, gql } = require('apollo-server');
const fs = require('fs');

const usersMock = [
	{ name: 'Bob', age: 23 },
	{ name: 'Lulu', age: 43 }
]

const resolvers = {
	Query: {
		users: () => usersMock,
	},
}

const typeDefs = fs.readFileSync('./type-defs.graphql');

const server = new ApolloServer({ typeDefs: gql`${typeDefs}`, resolvers});

server.listen({port: 4001}).then(({ url }) => {
	console.log(`🚀  Server ready at ${url}`);
});