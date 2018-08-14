// Copyright 2018 <Author>

#include "typing_machine.h"

TypingMachine::TypingMachine() {
	mNode = new Node(0x01);
	mCursor = mNode;
	mFirstNode = mNode;
	mLastNode = mNode;
	MAX_TYPE_LENGTH = 100;
	mCurrentLength = 0;
	return;
}

void TypingMachine::HomeKey() {
	mCursor = mFirstNode;

	return;
}

void TypingMachine::EndKey() {
	mCursor = mLastNode;

	return;
}

void TypingMachine::LeftKey() {
	if (mCursor->GetPreviousNode()) {
		mCursor = mCursor->GetPreviousNode();
	}
	return;
}

void TypingMachine::RightKey() {
	if (mCursor->GetNextNode()) {
		mCursor = mCursor->GetNextNode();
	}
	return;
}

bool TypingMachine::TypeKey(char key) {
	// return false : illegal input or over than max length
	if (key < 0x20 || key > 0x7e || mCurrentLength >= MAX_TYPE_LENGTH) {
		return false;
	}
	Node* node = mCursor->InsertPreviousNode(key);
	if (mCursor == mFirstNode) {
		mFirstNode = node;
	}
	else if (mCursor == mLastNode) {
		mLastNode = node->GetNextNode();
	}
	mCursor = node->GetNextNode();
	mCurrentLength++;
	return true;
}

bool TypingMachine::EraseKey() {
	if (mCurrentLength == 0) {
		return false;
	}
	if (mCursor->ErasePreviousNode()) {
		mCurrentLength--;
		// if the first node has been deleted, make it as mFirstNode
		if (mCursor->GetPreviousNode() == nullptr) {
			mFirstNode = mCursor;
		}
		return true;
	}
	return false;
}

std::string TypingMachine::Print(char separator) {
	Node* node = mFirstNode;
	std::string text = "";

	while (node) {
		if (node == mCursor && separator != '\0') {
			// if the char is overrided by cursor, add it behind of seprator
			text += separator;
			if (node->GetData() != 0x01) {
				text += node->GetData();
			}
		}
		else if (node->GetData() != 0x01) {
			text += node->GetData();
		}
		// set next pointor
		node = node->GetNextNode();
	}
	return text;
}
