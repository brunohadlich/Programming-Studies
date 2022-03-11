const { ApolloServer, gql } = require("apollo-server");
const { buildSubgraphSchema } = require("@apollo/federation");
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
	},
	{
		id: 3,
		title: 'I, Robot',
		author: 'Isaac Asimov',
		genre: 'SCIENCE_FICTION'
	}
];

const resolvers = {
	Book: {
		__resolveReference(bookReference) {
			console.log("Accessed Book.__resolveReference");
			return books.find(book => book.id == parseInt(bookReference.id));
		}
	},
	Query: {
		books(root, args, context, info) {
			console.log("Accessed Query.books");
			if (args.id) {
				return books.filter(book => parseInt(args.id) == book.id);
			}
			return books;
		}
	},
};

const typeDefs = fs.readFileSync('./library-type-defs.graphql');

const server = new ApolloServer({
	schema: buildSubgraphSchema([{ typeDefs: gql`${typeDefs}`, resolvers }]),
	introspection: true
});

server.listen({port: 4001}).then(({ url }) => {
	console.log(`🚀  Server ready at ${url}`);
});