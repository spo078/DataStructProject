#include "bst.hpp"

BST::BST() {
    root = nullptr;  // Initialize the root to nullptr
    size = 0;        // Initialize the size of the BST to 0
}


void BST::deleteTree(XPost* rt) {
    if (rt != nullptr) {
        deleteTree(rt->left);   // Delete left subtree
        deleteTree(rt->right);  // Delete right subtree
        delete rt;              // Delete the current node
    }
}

BST::~BST() {
    deleteTree(root);  // Use the helper function to delete the tree starting from the root
}

XPost* BST::createPost(float time, string content, int likes) {
    XPost* post = new XPost;
    post->postedTime = time;
    post->xContents = content;
    post->likes = likes;
    post->left = nullptr;  // Initialize left child to nullptr
    post->right = nullptr; // Initialize right child to nullptr
    return post;
}


void BST::insertPost(float time, string content, int likes) 
{
	XPost* addpost = createPost(time, content, likes);
	 if (this->root == nullptr) {
        root = addpost;
    } else {
        insertHelper(root, addpost);
    }
}


XPost* BST::insertHelper(XPost* rt, XPost* pst) {
    if (rt == nullptr) {
        return pst; // Base case: If the current node is null, the post should be inserted here.
    }

    if (pst->postedTime < rt->postedTime) {
        rt->left = insertHelper(rt->left, pst); // Recursively insert to the left.
        return rt; // Return the current (unchanged) node.
    } else if (pst->postedTime > rt->postedTime) {
        rt->right = insertHelper(rt->right, pst); // Recursively insert to the right.
        return rt; // Return the current (unchanged) node.
    }
 
    return rt; // Return the current node.
}



void BST::displayPosts() 
{
	displayHelper(root);
}

void BST::displayHelper(XPost* rt) {
    if (rt != nullptr) {
        // Recurse on the left child
        displayHelper(rt->left);

        // Process the current node (root of the subtree)
        cout << "Time: " << rt->postedTime << ", Content: " << rt->xContents << ", Likes: " << rt->likes << endl;

        // Recurse on the right child
        displayHelper(rt->right);
    }
}


XPost* BST::mostPopular()
{
    XPost* mostLiked = nullptr;
    mostPopularHelper(root, mostLiked);
    return mostLiked;

}

void BST::mostPopularHelper(XPost* rt, XPost*& mostLiked) {
    if (rt != nullptr) {
        // Check if the current post has more likes than the mostLiked post
        if (mostLiked == nullptr || rt->likes > mostLiked->likes) {
            mostLiked = rt;
        }

        // Recursively call the function for left and right subtrees
        mostPopularHelper(rt->left, mostLiked);
        mostPopularHelper(rt->right, mostLiked);
    }
}

