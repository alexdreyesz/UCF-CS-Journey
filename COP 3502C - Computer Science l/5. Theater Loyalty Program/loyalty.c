#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define MAXLEN 19


//Customer Structs
typedef struct customer {
	char name[MAXLEN + 1];
	int points;
} customer;


//Binary Search Tree Structs
typedef struct treenode {
	customer* cPtr;
	int size;
	struct treenode* left;
	struct treenode* right;
} treenode;


//Create A Customer
customer* create_customer(const char* name, int points) {

	customer* add_customer = (customer*)malloc(sizeof(customer));

	if (add_customer != NULL) {
		strncpy(add_customer->name, name, MAXLEN);
		add_customer->points = points;
	}

	return add_customer;
}


//Create A Node For The Tree
treenode* create_node(customer* cPtr) {

	treenode* add_node = (treenode*)malloc(sizeof(treenode));

	if (add_node != NULL) {
		add_node->cPtr = cPtr;
		add_node->left = add_node->right = NULL;
	}

	return add_node;
}


// Insert A Node On The Tree
treenode* insert_node(treenode* root, customer* cPtr) {

	if (root == NULL) {
		return create_node(cPtr);
	}

	int name_comparison = (strcmp(cPtr->name, root->cPtr->name));

	if (name_comparison < 0) {
		root->left = insert_node(root->left, cPtr);
	}

	if (name_comparison > 0) {
		root->right = insert_node(root->right, cPtr);
	}

	if (name_comparison == 0) {
		return root;
	}

	return root;
}


// Search A Customer Name In The Tree 
treenode* search_name(treenode* root, const char* name) {

	if (root == NULL) {
		return NULL;
	}

	int name_comparison = strcmp(name, root->cPtr->name);

	if (name_comparison < 0) {
		return search_name(root->left, name);
	}

	if (name_comparison > 0) {
		return search_name(root->right, name);
	}

	if (name_comparison == 0) {
		return root;
	}

	return root;
}


// Add Loyalty Points To A Customer
void add_points(treenode* root, const char* name, int loyalty_points) {

	treenode* name_found = search_name(root, name);

	if (name_found == NULL) {
		printf("%s not found\n", name);
	}

	if (name_found != NULL) {
		name_found->cPtr->points = loyalty_points;
		printf("%s %d\n", name, name_found->cPtr->points);
	}

}


// Substract Loyalty Points To A Customer
void substract_points(treenode* root, const char* name, int loyalty_points) {

	treenode* name_found = search_name(root, name);

	if (name_found == NULL) {
		printf("%s not found\n", name);
	}

	if (name_found != NULL) {
		name_found->cPtr->points = loyalty_points;
		printf("%s %d\n", name, name_found->cPtr->points);
	}

}


// Function to find the node with the minimum value in a tree
treenode* find_smallest_value(treenode* node) {

	while (node->left != NULL) {
		node = node->left;
	}

	return node;
}


// Function To Delete A Node From The Tree
treenode* delete_customer(treenode* root, const char* name) {

	if (root == NULL) {
		return root;
	}

	int name_comparison = strcmp(name, root->cPtr->name);

	if (name_comparison < 0) {
		root->left = delete_customer(root->left, name);
	}

	if (name_comparison > 0) {
		root->right = delete_customer(root->right, name);
	}

	if (name_comparison == 0) {

		if (root->left == NULL) {
			treenode* temporary = root->right;
			free(root->cPtr);
			free(root);
			return temporary;
		}

		if (root->right == NULL) {
			treenode* temporary = root->left;
			free(root->cPtr);
			free(root);
			return temporary;
		}

		treenode* temporary = find_smallest_value(root->right);

		strcpy(root->cPtr->name, temporary->cPtr->name);

		root->cPtr->points = temporary->cPtr->points;

		root->right = delete_customer(root->right, temporary->cPtr->name);
	}

	return root;
}


// Search Name And Depth For Customer 
int search_name_depth(treenode* root, const char* name, int depth) {

	if (root == NULL) {
		return -1;
	}

	int name_comparison = (strcmp(name, root->cPtr->name));

	if (name_comparison < 0) {
		return search_name_depth(root->left, name, depth + 1);
	}

	if (name_comparison > 0) {
		return search_name_depth(root->right, name, depth + 1);
	}

	if (name_comparison == 0) {
		printf("%s %d %d\n", name, root->cPtr->points, depth);
		return depth;
	}
}


// Count Smaller Name Order Before Customer Name 
int count_smaller_names(treenode* root, const char* name) {

	if (root == NULL) {
		return 0;
	}

	int count = 0;

	count = count + count_smaller_names(root->left, name);

	if (strcmp(root->cPtr->name, name) < 0) {
		count++;
	}

	count = count + count_smaller_names(root->right, name);

	return count;
}


//Free Binary Search Tree
void free_tree(treenode* root) {

	if (root != NULL) {
		free_tree(root->left);
		free_tree(root->right);
		free(root->cPtr);
		free(root);
	}
}

// Pre-Order Traversal The Binary Search Tree
void pre_order_traversal(treenode* root) {

	if (root != NULL) {
		printf("%s %d\n", root->cPtr->name, root->cPtr->points);
		pre_order_traversal(root->left);
		pre_order_traversal(root->right);
	}
}


//Main
int main() {

	int processes = 0;
	char options[15] = { 0 };
	int index = 0;
	char name[MAXLEN + 1];
	char* name_p = name;
	int loyalty_points = 0;
	int depth = 0;
	int smaller_names = 0;

	treenode* root = NULL;
	treenode* root_name = NULL;
	customer* add_customer = NULL;

	scanf("%d", &processes);


	for (int counter = 1; counter <= processes; counter++) {

		scanf("%s", &options);


		// Add Loyalty Points
		if (strcmp(options, "add") == 0) {

			scanf("%s", &name);
			name_p = name;

			scanf("%d", &loyalty_points);

			root_name = search_name(root, name_p);

			if (root_name != NULL) {
				add_points(root, name_p, loyalty_points);
			}

			if (root_name == NULL) {
				add_customer = create_customer(name_p, loyalty_points);
				root = insert_node(root, add_customer);
				printf("%s %d\n", name_p, loyalty_points);
			}


		}


		// Substract Loyalty Points
		if (strcmp(options, "sub") == 0) {

			scanf("%s", &name);
			name_p = name;

			scanf("%d", &loyalty_points);

			substract_points(root, name_p, loyalty_points);


		}


		// Delete Costumer
		if (strcmp(options, "del") == 0) {

			scanf("%s", &name);
			name_p = name;

			root_name = search_name(root, name_p);

			if (root_name != NULL) {
				root = delete_customer(root, name_p);
				printf("%s deleted\n", name_p);
			}

			if (root_name == NULL) {
				printf("%s not found\n", name_p);
			}

		}


		// Search Costumer
		if (strcmp(options, "search") == 0) {

			scanf("%s", &name);
			name_p = name;

			depth = search_name_depth(root, name_p, 0);

			if (depth == -1) {
				printf("%s not found\n", name_p);
			}


		}


		// Count Smaller Names
		if (strcmp(options, "count_smaller") == 0) {

			scanf("%s", &name);
			name_p = name;

			root_name = search_name(root, name_p);

			if (root_name != NULL) {
				smaller_names = count_smaller_names(root, name_p);
				printf("%d\n", smaller_names);
			}

			if (root_name == NULL) {
				printf("%s not found\n", name_p);
			}


		}

	}

	pre_order_traversal(root);

	free_tree(root);
	free_tree(root_name);

	return 0;
}