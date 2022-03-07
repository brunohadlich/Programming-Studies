const { ApolloServer, gql } = require("apollo-server");
const fs = require('fs');

const books = [
	{
		id: 1,
		title: 'Harry Potter',
		author: 'J. K. Rowling',
		genre: 'FANTASY_FICTION'
	},
	{
		id: 2,
		title: 'Foundation',
		author: 'Isaac Asimov',
		genre: 'SCIENCE_FICTION'
	}
]

const resolvers = {
	Query: {
		books: () => books,
	},
}

const typeDefs = fs.readFileSync('./type-defs.graphql');

const server = new ApolloServer({ typeDefs: gql`${typeDefs}`, resolvers });

server.listen({port: 4002}).then(({ url }) => {
	console.log(`🚀  Server ready at ${url}`);
});