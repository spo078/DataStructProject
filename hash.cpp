// CPP program to implement hashing with chaining
#include<iostream>
#include<sstream>
#include "hash.hpp"
using namespace std;

HashTable::HashTable()
{
	tableSize = M;
	numCollision = 0;
	
	table = new XUser*[tableSize];
	for(int i = 0; i < tableSize; i++) {
		table[i] = nullptr;
	}
}

XUser* HashTable::createUser(string username, string userBio)
{
	XUser* user = new XUser;
	user->username = username;
	user->userBio = userBio;
	user->postCount = 0;
	user->bst = new BST;
}

unsigned int HashTable::hashFunction(string username)
{
	unsigned int sum = 0;
	for(int i = 0; i < username.length(); i++) {
		sum += username[i];
	}
	sum = sum % this->tableSize;
	return sum;
}


//function to insert a new user into hash table (posts inserted separately)
XUser* HashTable::insertUser(string username, string userBio) {
    unsigned int index = hashFunction(username);

    // Check if username already exists
    XUser* temp = table[index];
    while (temp != nullptr) {
        if (temp->username == username) {
            return nullptr; // Username already exists
        }
        temp = temp->next;
    }

    // Create a new user and insert at the beginning of the chain
    XUser* newUser = createUser(username, userBio);
    newUser->next = table[index];
    table[index] = newUser; // Update the head of the linked list

    // Update collision count if necessary
    if (newUser->next != nullptr) {
        numCollision++;
    }

    return newUser; // Return the newly created user
}


XUser* HashTable::searchUser(string username)
{
	unsigned int index = hashFunction(username);
	XUser* temp = this->table[index];
	while(temp != nullptr) {
		if(temp->username == username)
			return temp;
		temp = temp->next;
	}
	return NULL;
	
}

void HashTable::printUsers() {
    for (int i = 0; i < tableSize; i++) {
        cout << i << '|'; // Print the bucket index

        if (table[i] == nullptr) {
            cout << "NULL\n"; // Print NULL for empty bucket
        } else {
            XUser* temp = table[i]; // Use a temporary pointer
            while (temp != nullptr) {
                cout << temp->username; // Print the username
                temp = temp->next; // Move to the next node
                if (temp != nullptr) {
                    cout << "-->"; // Print arrow if there is a next node
                }
            }
            cout << "->NULL\n"; // Indicate the end of the list
        }
    }
}


void HashTable::printAllPostByUser(string username) {
    XUser* to_print = searchUser(username);
    if(to_print == NULL) {
        cout << "User does not exist, try again..." << '\n';
    } else {
        cout << to_print->username << ":" << '\n';
        cout << "| userBio: " << to_print->userBio << '\n';
        cout << "| postCount: " << to_print->postCount << '\n';
        cout << "| Posts: " << '\n';
        if (to_print->bst != NULL) {
            to_print->bst->displayPosts();
        } else {
            cout << "No posts available." << '\n';
        }
    }
}


void HashTable::printMostLikedPost() {
    XPost* mostLikedOverall = nullptr;

    for (int i = 0; i < tableSize; i++) {
        XUser* currentUser = table[i];
        while (currentUser != nullptr) {
            if (currentUser->bst != nullptr) {
                XPost* mostLikedForUser = currentUser->bst->mostPopular();
                if (mostLikedForUser != nullptr && (mostLikedOverall == nullptr || mostLikedForUser->likes > mostLikedOverall->likes)) {
                    mostLikedOverall = mostLikedForUser;
                }
            }
            currentUser = currentUser->next;
        }
    }

    if (mostLikedOverall != nullptr) {
        cout << "Most Liked Post: " << endl;
        //cout << "Username" << mostLikedOverall->
        cout << "Time: " << mostLikedOverall->postedTime << ", Content: " << mostLikedOverall->xContents << ", Likes: " << mostLikedOverall->likes << endl;
    } else {
        cout << "No posts available in the HashTable." << endl;
    }
}


int HashTable::longestChain() {
    int maxLength = 0;

    for (int i = 0; i < tableSize; i++) {
        int chainLength = 0;
        XUser* temp = table[i];

        while (temp != nullptr) {
            chainLength++;
            temp = temp->next;
        }

        if (chainLength > maxLength) {
            maxLength = chainLength;
        }
    }

    return maxLength;
}

    
