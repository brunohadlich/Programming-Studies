const { ApolloServer, gql } = require('apollo-server');
const { buildSubgraphSchema } = require('@apollo/federation');
const fs = require('fs');

const users = [
	{ id: 1, name: 'Bob', age: 23, books: [1, 2, 3] },
	{ id: 2, name: 'Lulu', age: 43, books: [2] }
];

const resolvers = {
	Book: {
		readers(book) {
			console.log("Accessed Book.readers");
			return users.filter(user => user.books.some(bookId => bookId == book.id));
		}
	},
	User: {
		books(user) {
			console.log("Accessed User.books");
			return user.books.map(bookId => ({ __typename: "Book", id: bookId }) );
		}
	},
	Query: {
		users(root, args, context, info) {
			if (args.id) {
				return users.filter(user => parseInt(args.id) == user.id);
			}
			return users;
		},
	}
};

const typeDefs = fs.readFileSync('./user-type-defs.graphql');

const server = new ApolloServer({
	schema: buildSubgraphSchema([{ typeDefs: gql`${typeDefs}`, resolvers }]),
	introspection: true
});

server.listen({port: 4002}).then(({ url }) => {
	console.log(`🚀  Server ready at ${url}`);
});