// Ctrl+F "BUG:" to skip to segments that were changed

/******************************************************************************
* An implementatrion of a double-linked list (http://en.wikipedia.org/wiki/Double_linked_list)
* This code has 13 bugs. You don't have to find all of them.
* Some bugs will be easy to find, some will be quite hard.
* You do not need to understand what this code does in order to find the easier bugs,
* and you certainly don't need to understand it to finish the spike.
* You'll need to understand the code to go 13 for 13, but consider that a challenge,
* rather than a requirement.
* As its written, none of the bugs will prevent the the code from compiling.
* (Tested with Visual Studio 2010 under Windows 7)
******************************************************************************/

#include <string>
#include <iostream>
// BUG: <stdexcept> is never used
// CHANGE: Removed "#include <stdexcept>

// BUG: "using namespace" inside a header causes type name problems e.g. "string" cannot be resolved if header has "using namespace std;" and defines my_namespace::string
// CHANGE: Removed "using namespace std;" and changed everything from the STL below to use the std:: prefix

/**************************************************************************************************
* DoubleLinkedNode class definition. DoubleLinkedNode forms a single node in a doubly linked list.
* Templates are used so the list may be made of any datatype.
***************************************************************************************************/
template <class DataType>
class DoubleLinkedNode {
public:
	typedef DoubleLinkedNode<DataType> Node;
private:
	//The data contained in this node
	DataType value;
	//The next Node in the list
	Node* nextnode;
	//The previous Node in the list
	Node* previousnode;
public:
	/*********************************************************************************************
	* DoubleLinkedNode Class Constructor: Creates DoubleLinkedNode object with value = initvalue
	*********************************************************************************************/
	DoubleLinkedNode(const DataType initvalue) : value(initvalue) {
		std::cout << "Creating Node..." << std::endl;
	}

	/*********************************************************************************************
	* DoubleLinkedNode Class Destructor: Destroys DoubleLinkedNode object, freeing memory
	*********************************************************************************************/
	~DoubleLinkedNode() {
		std::cout << "Destroying Node... " << std::endl;
	}

	/*********************************************************************************************
	* Function: Inserts the Node newnode behind this Node, moving all other Nodes down one.
	* Input: Node*. The Node to be inserted.
	* Output: -
	*********************************************************************************************/
	void insertNodeAfter(Node* newnode) {
		// BUG: newnode no NULL check
		// CHANGE: Added the if conditional block below
		if (newnode != NULL) {
			if (nextnode != NULL) {
				newnode->insertNodeAfter(nextnode);
			}
			setNext(newnode);
			newnode->setPrevious(this);
		}
	};

	/*********************************************************************************************
	* Function: Inserts the Node newnode in front of this Node, moving all other Nodes, including this node down one.
	* Input: Node*. The Node to be inserted.
	* Output: -
	*********************************************************************************************/
	void insertNodeBefore(Node* newnode) {
		// BUG: newnode no NULL check
		// CHANGE: Added the if conditional block below
		if (newnode != NULL) {
			if (previousnode != NULL) {
				// BUG: Argument to method is nextnode when it should be previousnode
				// CHANGE: Changed argument to previousnode
				newnode->insertNodeBefore(previousnode);
			}
			setPrevious(newnode);
			newnode->setNext(this);
		}
	};

	/*********************************************************************************************
	* Function: Removes this Node from the list, reconnecting other nodes so the list is unbroken.
	* Input: -
	* Output: -
	*********************************************************************************************/
	void dropNode() {
		if (previousnode) {
			previousnode->setNext(nextnode);
		}
		if (nextnode) {
			nextnode->setPrevious(previousnode);
		}
		delete this;
	};

	/*********************************************************************************************
	* Function: Returns the next Node in the list.
	* Input: -
	* Output: Node*. The next Node in the list.
	*********************************************************************************************/
	Node* getNext() const {
		return nextnode;
	};

	/*********************************************************************************************
	* Function: Returns the previous Node in the list.
	* Input: -
	* Output: Node*. The previous Node in the list.
	*********************************************************************************************/
	Node* getPrevious() const {
		return previousnode;
	};

	/*********************************************************************************************
	* Function: Sets the next Node in the list.
	* Input: Node*. A pointer to the Node that is to be made the next Node in the list.
	* Output: -
	*********************************************************************************************/
	void setNext(Node* N) {
		nextnode = N;
	}

	/*********************************************************************************************
	* Function: Sets the previous Node in the list.
	* Input: Node*. A pointer to the Node that is to be made the previous Node in the list.
	* Output: -
	*********************************************************************************************/
	void setPrevious(Node* N) {
		previousnode = N;
	}

	/*********************************************************************************************
	* Function: Returns the data contained in this this Node.
	* Input: -
	* Output: const DataType&. The data contained in this Node.
	*********************************************************************************************/
	const DataType& getValue() const {
		return value;
	};

};

/**************************************************************************************************
* DoubleLinkedList class definition. Constructs a double linked list made up of DoubleLinkedNode objects.
* Templates are used so the list and its nodes may be made of any datatype.
***************************************************************************************************/
template <class T>
class DoubleLinkedList {
private:
	typedef DoubleLinkedNode<T> Node;

	//The first node in the list
	Node* first;
	//The last node in the list
	Node* last;
	//The length of the list
	int _length;
public:
	/*********************************************************************************************
	* List Class Constructor: Creates List object.
	* The list is created without any contents.
	*********************************************************************************************/
	DoubleLinkedList() : first(NULL), last(NULL), _length(0) {};

	/*********************************************************************************************
	* List Class Destructor: Destroys all nodes allocated as a part of the list and frees memory.
	*********************************************************************************************/
	~DoubleLinkedList() {
		// BUG: No NULL check on first (NULL->getNext())
		// CHANGE: Added the if conditional block below
		if (first != NULL) {
			while (first->getNext() != NULL) {
				first->getNext()->dropNode();
			}
			// BUG: first is never deleted
			// CHANGE: Added "delete first;"
			delete first;
		}
	};


	/*********************************************************************************************
	* Function: Appends the Node newelement to the end of the List
	*********************************************************************************************/
	void append(const T &newelement) {
		Node *N = new Node(newelement);

		if (first == NULL) {
			first = N;
			last = N;
			_length = 1;
		} else {
			last->insertNodeAfter(N);
			last = N;
			_length++;
		}
	};

	/*********************************************************************************************
	* Function: Appends the Node newelement to the end of the List
	*********************************************************************************************/
	void prepend(const T &newelement) {
		Node *N = new Node(newelement);

		if (first == NULL) {
			first = N;
			last = N;
			_length = 1;
		} else {
			first->insertNodeBefore(N);
			first = N;
			_length++;
		}
	};

	/*********************************************************************************************
	* Function: Drops the first Node found with a value matching element, if one exits. If a node
	* was found and dropped, true is returned, false otherwise.
	*********************************************************************************************/
	bool drop(const T& element) {
		// BUG: No NULL check on first
		// CHANGE: Added the if conditional block below
		if (first != NULL) {
			if (first->getValue() == element) {
				dropFirst();
				return true;
			}
			else if (last->getValue() == element) {
				dropLast();
				return true;
			}

			Node *N = first;
			while (N != last) {
				if (N->getValue() == element) {
					N->dropNode();
					// BUG: Length not decremented
					// CHANGE: Added "--_length;"
					--_length;
					return true;
				}
				// BUG: N not incremented
				// CHANGE: Added "N = N->getNext();"
				N = N->getNext();
			}
		}
		return false;
	};

	/*********************************************************************************************
	* Function: Drops the first Node in the List.
	*********************************************************************************************/
	void dropFirst() {
		// BUG: No NULL check on first
		// CHANGE: Added the if conditional block below
		if (first != NULL) {
			Node* oldFirst = first;
			first = first->getNext();
			oldFirst->dropNode();
			// BUG: Length not decremented
			// CHANGE: Added "--_length;"
			--_length;
			// BUG: last not set to NULL if length goes to 0
			// CHANGE: Setting last to NULL if first is NULL
			if (first == NULL) {
				last = NULL;
			}
		}
	};

	/*********************************************************************************************
	* Function: Drops the last Node in the List.
	*********************************************************************************************/
	void dropLast() {
		// BUG: No NULL check
		// CHANGE: Added the if conditional block below
		if (last != NULL) {
			Node* oldLast = last;
			last = last->getPrevious();
			oldLast->dropNode();
			// BUG: Length not decremented
			// CHANGE: Added "--_length;"
			--_length;
			// BUG: last not set to NULL if length goes to 0
			// CHANGE: Setting first to NULL if last is NULL
			if (last == NULL) {
				first = NULL;
			}
		}
	};

	/*********************************************************************************************
	* Function: Iterates over the contents of the list, printing the value of each node in turn.
	*********************************************************************************************/
	void print(void) {
		// BUG: N not initialized
		// CHANGE: Changed line to "Node* N = first;"
		Node* N = first;
		// BUG: Loop doesn't write the value of last
		// CHANGE: Changed loop condition to "N != NULL"
		while (N != NULL) {
			std::cout << N->getValue() << std::endl;
			// BUG: N not incremented
			// CHANGE: Added line "N = N->getNext();"
			N = N->getNext();
		}
		std::cout << "-----------------------------------------------" << std::endl;
	}
};

int main(int argc, char* argv[]) {
	std::string s1("One");
	std::string s2("Two");
	std::string s3("Three");
	std::string s4("Four");
	std::string s5("Five");
	std::string s6("Six");

	// BUG: L not initialized
	// CHANGE: Changed line to "DoubleLinkedList<std::string>* L = new DoubleLinkedList<std::string>();"
	DoubleLinkedList<std::string>* L = new DoubleLinkedList<std::string>();
	//Add some numbers to the list
	L->append(s3);
	L->append(s4);
	L->append(s5);
	L->print();		//Looks good, but we forgot One and Two
					//Lets add them
	L->prepend(s1);
	L->prepend(s2);
	L->print();		//Oh, no - they're on backwards
					//Remove them
	L->drop(s1);
	L->drop(s2);
	L->print();		//Yep, they're gone
					//Add them again, this time in the right order.
	L->prepend(s2);
	L->prepend(s1);
	L->print();		//All good
					//add the last number
	L->prepend(s6);
	L->print();		//Done!

	std::cin.ignore();

	// BUG: L is never deleted
	// CHANGE: Added line "delete L;"
	delete L;

	return 0;
}
