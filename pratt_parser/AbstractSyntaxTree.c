typedef struct Ast AbstractSyntaxTree;
typedef struct Ast {
	enum typez type;
	AbstractSyntaxTree* left;
	AbstractSyntaxTree* right;
	char* val;
} AbstractSyntaxTree;

AbstractSyntaxTree* new_Ast(enum typez type, AbstractSyntaxTree* left, AbstractSyntaxTree* right, char* val) {
	AbstractSyntaxTree* rv = malloc(sizeof(AbstractSyntaxTree));
	rv->type = type;
	rv->val = val;
	rv->left = left;
	rv->right = right;
	return rv;
}


void print_Ast(AbstractSyntaxTree* root) {
	if (root == 0)
		return;

	printf("%s ", root->val);
	print_Ast(root->left);
	printf(" ");
	print_Ast(root->right);
	printf("");
	
}