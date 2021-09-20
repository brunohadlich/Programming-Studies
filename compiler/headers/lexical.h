enum token_type {
	logical_op,//&& || !
	arithmetic_op,//+ - * /
	relational_op,//> < == >= <=
	assignment_op,//= += -= *= /=
	identifier,
	if_keyword,
	while_keyword,
	literal,//23 4.673 .85 4.
	print,//function, e.g. print(variable)
	semicolon,
	open_parenthesis,
	close_parenthesis,
	type//int32 float32
};

struct token {
	char *lexeme;
	enum token_type type;
	void *attribute;
};