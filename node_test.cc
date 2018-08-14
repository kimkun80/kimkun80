// Copyright 2018 Minkyu Jo

#include "node.h"
#include "node_test.h"
#include "test.h"

class NodeConstructorTestSuite
{
private:
  static void SingleNodeTest() {
    Node *node = new Node('A');
    ASSERT_EQ(node->GetData(), 'A');
    delete node;
  }
  
  static void InsertPrevNodeTest() {
	  Node *node = new Node('A');
	  node->InsertPreviousNode('B');
	  ASSERT_EQ(node->GetPreviousNode()->GetData(), 'B');
	  delete node;
  }

  static void InsertNextNodeTest() {
	  Node *node = new Node('A');
	  node->InsertNextNode('C');
	  ASSERT_EQ(node->GetNextNode()->GetData(), 'C');
	  delete node;
  }

  static void ErasePrevNodeTest() {
	  Node *node = new Node('A');
	  ASSERT_EQ(node->GetData(), 'A');
	  Node *nextNode = node->InsertNextNode('B');
	  
	  // erase a inserted node
	  bool result = nextNode->ErasePreviousNode();
	  ASSERT_TRUE(result);
	  ASSERT_TRUE(nextNode->GetPreviousNode() == nullptr);

	  // try erase a empty node
	  result = nextNode->ErasePreviousNode();
	  ASSERT_FALSE(result);
	  ASSERT_TRUE(nextNode->GetPreviousNode() == nullptr);

	  // delete node;
	  delete nextNode;
  }

  static void EraseNextNodeTest() {
	  Node *node = new Node('A');
	  ASSERT_EQ(node->GetData(), 'A');
	  node->InsertNextNode('B');

	  // erase a inserted node
	  bool result = node->EraseNextNode();
	  ASSERT_TRUE(result);
	  ASSERT_TRUE(node->GetNextNode() == nullptr);

	  // try erase a empty node
	  result = node->EraseNextNode();
	  ASSERT_FALSE(result);
	  ASSERT_TRUE(node->GetNextNode() == nullptr);

	  // delete node;
	  delete node;
  }

  static void MoveLeftTest() {
	  Node* node = getDummyNode(2);

	  for (int i = 5; i > 0; i--) {
		  int readData = node->GetData() - '0';
		  ASSERT_EQ(i, readData);
		  node = node->GetPreviousNode();
		  // node->EraseNextNode();
	  }
 	  
	  ASSERT_TRUE(node == nullptr);
  }

  static void MoveRightTest() {
	  Node* node = getDummyNode(0);

	  for (int i = 1; i < 6; i++) {
		  int readData = node->GetData() - '0';
		  ASSERT_EQ(i, readData);
		  node = node->GetNextNode();
		  // node->EraseNextNode();
	  }

	  ASSERT_TRUE(node == nullptr);
  }

  static Node* getDummyNode(int start) {
	  Node *tail = new Node('5');
	  Node* front = tail->InsertPreviousNode('1');
	  Node *center = tail->InsertPreviousNode('2');
	  tail->InsertPreviousNode('3');
	  tail->InsertPreviousNode('4');
	   
	  if (start == 0) {
		  return front;
	  }
	  else if (start == 1) {
		  return center;
	  }
	  else {
		  return tail;
	  }
  }

public:
  static void RunTest() {
    SingleNodeTest();
    // add more..
	InsertPrevNodeTest();
	InsertNextNodeTest();
	ErasePrevNodeTest();
	EraseNextNodeTest();
	MoveLeftTest();
	MoveRightTest();
  }
};

class SomeOtherTestSuite
{
private:

public:
  static void RunTest() {
    // add more..
  }
};

void NodeTest() {
  NodeConstructorTestSuite::RunTest();
  // add more..
}