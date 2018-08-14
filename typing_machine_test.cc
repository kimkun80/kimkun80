
#include "typing_machine.h"
#include "typing_machine_test.h"
#include "test.h"

class TmConstructorTestSuite
{
private:
	static void BarSeparatorTest() {
		TypingMachine tm;
		ASSERT_EQ(tm.Print('|'), std::string("|"));
	}

	static void BarSeparatorWithNullTest() {
		TypingMachine tm;
		ASSERT_EQ(tm.Print('\0'), std::string(""));
	}
public:
	static void RunTest() {
		BarSeparatorTest();
		// add more..
		BarSeparatorWithNullTest();
	}
};

class TypeKeyTestSuite
{
private:
	static void InsertMultiCharTest() {
		TypingMachine tm;
		tm.TypeKey('A');
		tm.TypeKey('B');
		tm.TypeKey('C');
		ASSERT_EQ(tm.Print('|'), std::string("ABC|"));
		ASSERT_EQ(tm.Print('\0'), std::string("ABC"));
	}

	static void InsertInvalidCharTest() {
		TypingMachine tm;
		tm.TypeKey(0x01);
		ASSERT_EQ(tm.Print('|'), std::string("|"));
		tm.TypeKey(0x19);
		ASSERT_EQ(tm.Print('|'), std::string("|"));
		tm.TypeKey(0x7f);
		ASSERT_EQ(tm.Print('|'), std::string("|"));

		tm.TypeKey(0x20);
		ASSERT_EQ(tm.Print('\0'), std::string(" "));
		tm.EraseKey();

		tm.TypeKey(0x7e);
		std::string temp = tm.Print('\0');
		ASSERT_EQ(tm.Print('\0'), std::string("~"));
	}

	static void InsertManyCharTest() {
		TypingMachine tm;
		std::string result = "";
		for (int i = 0; i < 100; i++) {
			tm.TypeKey('A');
			result += "A";
			ASSERT_EQ(tm.Print('\0'), result);
		}

		// input bound value
		tm.TypeKey('A');
		ASSERT_EQ(tm.Print('\0'), result);

		// remove a single char
		tm.EraseKey();
		std::string temp = tm.Print('\0');
		ASSERT_EQ(tm.Print('\0'), result.substr(0, result.length() - 1));
	}


public:
	static void RunTest() {
		// add more..
		InsertMultiCharTest();
		InsertManyCharTest();
		InsertInvalidCharTest();
	}
};

class EraseTestSuite
{
private:

	static void EraseCharTest() {
		TypingMachine tm;
		std::string result = "";
		bool ret = false;
		tm.TypeKey('A');
		ret = tm.EraseKey();
		ASSERT_TRUE(ret);
		ASSERT_EQ(tm.Print('\0'), "");

		ret = tm.EraseKey();
		ASSERT_FALSE(ret);

		for (int i = 0; i < 5; i++) {
			tm.TypeKey('A');
			result += "A";
			ASSERT_EQ(tm.Print('\0'), result);
		}
		// remove a single char
		tm.EraseKey();
		ASSERT_EQ(tm.Print('\0'), result.substr(0, result.length() - 1));
	}
public:
	static void RunTest() {
		EraseCharTest();
	}
};


class CursorTestSuite
{
private:
	static void MoveHomeTest() {
		TypingMachine tm;
		std::string result = "";
		for (int i = 0; i < 5; i++) {
			tm.TypeKey('A');
			result += "A";
			ASSERT_EQ(tm.Print('|'), result + "|");
		}
		tm.HomeKey();
		ASSERT_EQ(tm.Print('|'), "|AAAAA");
	}

	static void MoveEndTest() {
		TypingMachine tm;
		std::string result = "";
		for (int i = 0; i < 5; i++) {
			tm.TypeKey('A');
			result += "A";
			ASSERT_EQ(tm.Print('|'), result + "|");
		}

		tm.HomeKey();
		tm.EndKey();

		ASSERT_EQ(tm.Print('|'), "AAAAA|");
	}

	static void MoveLeftTest() {
		TypingMachine tm;
		std::string result = "";
		for (int i = 0; i < 5; i++) {
			tm.TypeKey('A');
			result += "A";
			ASSERT_EQ(tm.Print('|'), result + "|");
		}
		ASSERT_EQ(tm.Print('|'), "AAAAA|");
		tm.LeftKey();
		ASSERT_EQ(tm.Print('|'), "AAAA|A");
		tm.LeftKey();
		ASSERT_EQ(tm.Print('|'), "AAA|AA");
		tm.LeftKey();
		ASSERT_EQ(tm.Print('|'), "AA|AAA");
		tm.LeftKey();
		ASSERT_EQ(tm.Print('|'), "A|AAAA");
		tm.LeftKey();
		ASSERT_EQ(tm.Print('|'), "|AAAAA");
		//tm.LeftKey();
		//ASSERT_EQ(tm.Print('|'), "|AAAAA");
	}

	static void MoveRightTest() {
		TypingMachine tm;
		std::string result = "";
		for (int i = 0; i < 5; i++) {
			tm.TypeKey('A');
			result += "A";
			ASSERT_EQ(tm.Print('|'), result + "|");
		}

		tm.HomeKey();
		ASSERT_EQ(tm.Print('|'), "|AAAAA");
		tm.RightKey();
		ASSERT_EQ(tm.Print('|'), "A|AAAA");
		tm.RightKey();
		ASSERT_EQ(tm.Print('|'), "AA|AAA");
		tm.RightKey();
		ASSERT_EQ(tm.Print('|'), "AAA|AA");
		tm.RightKey();
		ASSERT_EQ(tm.Print('|'), "AAAA|A");
		tm.RightKey();
		ASSERT_EQ(tm.Print('|'), "AAAAA|");
		tm.RightKey();
		ASSERT_EQ(tm.Print('|'), "AAAAA|");
	}
public:
	static void RunTest() {
		MoveHomeTest();
		MoveEndTest();
		MoveLeftTest();
		MoveRightTest();
	}
};

void TypingMachineTest() {
	TmConstructorTestSuite::RunTest();
	// add more..
	TypeKeyTestSuite::RunTest();
	EraseTestSuite::RunTest();
	CursorTestSuite::RunTest();
	// ASSERT_EQ("", "|AAAA");
}