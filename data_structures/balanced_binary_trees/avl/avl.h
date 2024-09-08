struct node {
	int height;
	struct node *left;
	struct node *right;
	int value;
};

int exists(struct node *tree, int value);
int delete(struct node *tree, int value);
struct node *insert(struct node *tree, int value);
