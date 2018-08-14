// Copyright 2018 <Author>

#include "node.h"

Node::Node(char data) {
	mData = data;
	mPrevNode = nullptr;
	mNextNode = nullptr;
	return;
}

char Node::GetData() {
	return mData;
}

Node* Node::GetPreviousNode() {
	return mPrevNode;
}

Node* Node::GetNextNode() {
	return mNextNode;
}

Node* Node::InsertPreviousNode(char data) {
	// generate a new node inserted
	Node* newNode = new Node(data);
	newNode->setNextNode(this);
	newNode->setPrevNode(mPrevNode);

	// if there is a prev node, modify a next pointer to new node
	if (GetPreviousNode()) {
		GetPreviousNode()->setNextNode(newNode);
	}

	// set mPrevNode to a new node
	setPrevNode(newNode);
	return newNode;
}

Node* Node::InsertNextNode(char data) {
	Node* newNode = new Node(data);
	newNode->setPrevNode(this);
	newNode->setNextNode(mNextNode);

	// if there is a next node, modify a prev pointer to new node
	if (GetNextNode()) {
		GetNextNode()->setPrevNode(newNode);
	}

	// set mNextNode to a new node
	setNextNode(newNode);

	return newNode;
}

bool Node::ErasePreviousNode() {
	// if there is no prev node, do nothing
	if (GetPreviousNode()) {
		Node* erasedNode = GetPreviousNode();
		Node* targetNode = GetPreviousNode()->GetPreviousNode();

		// update a new node info to prev 
		if (targetNode) {
			targetNode->setNextNode(this);
			setPrevNode(targetNode);
		}
		else {
			setPrevNode(nullptr);
		}

		// delete a node to prevent memory leak
		delete erasedNode;
		return true;
	}
	return false;
}

bool Node::EraseNextNode() {
	if (GetNextNode()) {
		Node* erasedNode = this->mNextNode;
		Node* targetNode = GetNextNode()->GetNextNode();
		
		if (targetNode) {
			setNextNode(targetNode);
			targetNode->setPrevNode(this);
		}
		else {
			setNextNode(nullptr);
		}
		
		delete erasedNode;
		return true;
	}
	return false;
}

void Node::setPrevNode(Node* node) {
	mPrevNode = node;
}

void Node::setNextNode(Node* node) {
	mNextNode = node;
}