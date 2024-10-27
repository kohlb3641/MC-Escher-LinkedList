// Brendt Kohl, Connor Simon
using namespace std;
#include "LinkedList.h"
#include <iostream>

int main()
{
	ListNode nodeArray[16];
	cout << "Hello world" << endl;

}

void createMap(DDLinkedList list)
{
	// Create the nodes first
	ListNode* node16 = new ListNode(16, false);
	ListNode* node15 = new ListNode(15, true);
	ListNode* node14 = new ListNode(14, false);
	ListNode* node13 = new ListNode(13, false);
	ListNode* node12 = new ListNode(12, false);
	ListNode* node11 = new ListNode(11, false);
	ListNode* node10 = new ListNode(10, false);
	ListNode* node9 = new ListNode(9, false);
	ListNode* node8 = new ListNode(8, true);
	ListNode* node7 = new ListNode(7, false);
	ListNode* node6 = new ListNode(6, false);
	ListNode* node5 = new ListNode(5, false);
	ListNode* node4 = new ListNode(4, false);
	ListNode* node3 = new ListNode(3, false);
	ListNode* node2 = new ListNode(2, false);
	ListNode* node1 = new ListNode(1, false);

	// Set directional pointers using the setter methods

	//for node16
	node16->setNorth(node2);
	node16->setSouth(node15);
	node16->setEast(node4);
	node16->setWest(node11);

	// For node15
	node15->setNorth(node16);
	node15->setSouth(node3);
	node15->setEast(nullptr);
	node15->setWest(node14);

	// For node14
	node14->setNorth(nullptr);
	node14->setSouth(node2);
	node14->setEast(node15);
	node14->setWest(node13);

	// For node13
	node13->setNorth(node12);
	node13->setSouth(node1);
	node13->setEast(node14);
	node13->setWest(node9);

	// For node12
	node12->setNorth(node1);
	node12->setSouth(node13);
	node12->setEast(nullptr);
	node12->setWest(nullptr);

	// For node11
	node11->setNorth(node10);
	node11->setSouth(nullptr);
	node11->setEast(node16);
	node11->setWest(nullptr);

	// For node10
	node10->setNorth(node9);
	node10->setSouth(node11);
	node10->setEast(node1);
	node10->setWest(nullptr);

	// For node9
	node9->setNorth(node4);
	node9->setSouth(node10);
	node9->setEast(node13);
	node9->setWest(node8);

	// For node8
	node8->setNorth(nullptr);
	node8->setSouth(node9);
	node8->setEast(nullptr);
	node8->setWest(nullptr);

	// For node7
	node7->setNorth(nullptr);
	node7->setSouth(nullptr);
	node7->setEast(node6);
	node7->setWest(node8);

	// For node6
	node6->setNorth(nullptr);
	node6->setSouth(nullptr);
	node6->setEast(node5);
	node6->setWest(node7);

	// For node5
	node5->setNorth(node4);
	node5->setSouth(nullptr);
	node5->setEast(nullptr);
	node5->setWest(node6);

	// For node4
	node4->setNorth(node3);
	node4->setSouth(node5);
	node4->setEast(node9);
	node4->setWest(node16);

	// For node3
	node3->setNorth(node15);
	node3->setSouth(node4);
	node3->setEast(nullptr);
	node3->setWest(node2);

	// For node2
	node2->setNorth(node14);
	node2->setSouth(node16);
	node2->setEast(node3);
	node2->setWest(node1);

	//for node1
	node1->setNorth(node13);
	node1->setSouth(node12);
	node1->setEast(node2);
	node1->setWest(node10);
}