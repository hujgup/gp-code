#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Spike13/MessageDispatcher.h"
#include "../Spike13/Message.h"
#include "../Spike13/BinaryReader.h"
#include "../Spike13/BinaryWriter.h"
#include "../Spike13/Event.h"
#include "../Spike13/Inventory.h"
#include "../Spike13/Player.h"
#include "../Spike13/Command.h"
#include "../Spike13/CommandResult.h"
#include "../Spike13/SuccessState.h"
#include "../Spike13/MainMenu.h"
#include "../Spike13/WorldSwitchMessage.h"
#include "../Spike13/InventoryView.h"
#include <thread>
#include <functional>

using namespace std;
using namespace placeholders;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Spike13Tests
{
	class TestMessage : public Message {
	public:
		TestMessage(TestMessage& copyMe) {
			string worldName;
			copyMe.read() >> worldName;
			this->write() << worldName;
		};
		TestMessage(string worldName) : Message(worldName) {
		};
		TestMessage() {
		};
		virtual string type_name() const override {
			return "TestMessage";
		};
		virtual time_t timeout() const override {
			return 50;
		};
		virtual Message* clone() override {
			return new TestMessage(*this);
		};
	};

	class Timeout {
	private:
		time_t _timeout;
		thread _t;
		void wait(function<void()> callback) {
			this_thread::sleep_for(chrono::milliseconds(_timeout));
			callback();
		};
	public:
		Timeout(time_t timeout) {
			_timeout = timeout;
		};
		void start(function<void()> callback) {
			_t = thread(bind(&Timeout::wait,this,_1),callback);
			_t.detach();
		};
	};

	TEST_CLASS(UnitTest1)
	{
	public:
		// Test: Message event firing
		TEST_METHOD(MessageEvents) {
			MessageDispatcher m;
			string msg = "hello world";
			bool seen = false;
			m[TestMessage()].event() += [&seen,&msg](MessageDispatcher& sender,Message& message) {
				seen = true;
				string msg2;
				message.read() >> msg2;
				Assert::AreEqual<string>(msg,msg2,L"Input message was not the same as the output message.");
			};
			m.dispatch(TestMessage(msg));
			this_thread::sleep_for(chrono::milliseconds(55));
			if (!seen) {
				Assert::Fail(L"Timeout. Event was not fired.");
			}
		};
		// Test: Message blackboard functionality
		TEST_METHOD(MessageBlackboard) {
			MessageDispatcher m;
			string msg = "hello world 2";
			m.dispatch(TestMessage(msg));
			Timeout t(25);
			bool seen = false;
			t.start([&msg,&m,&seen]() {
				seen = true;
				Assert::IsTrue(m[TestMessage()].has_held_message(),L"Message must be held.");
				Message* ptr = m[TestMessage()].held_message();
				string msg2;
				ptr->read() >> msg2;
				Assert::AreEqual<string>(msg,msg2,L"Input message was not the same as the output message.");
			});
			this_thread::sleep_for(chrono::milliseconds(55));
			if (!seen) {
				Assert::Fail(L"Timeout. Timer did not run callback function.");
			}
		};
		// Test: Item naming
		TEST_METHOD(ItemNaming) {
			unsigned long id = 342;
			string name = "test item";
			string desc = "test desc";
			Player p;
			Item i = Item::create(id,name,desc,p);
			unsigned long i2 = i.id();
			string n2 = i.name();
			string d2 = i.desc();
			Assert::AreEqual(id,i2,L"IDs did not match.");
			Assert::AreEqual(name,n2,L"Names did not match.");
			Assert::AreEqual(desc,d2,L"Descs did not match.");
		};
		// Test: Command overloading
		TEST_METHOD(CommandOverloads) {
			Command c;
			c.add_overload(0, [](const vector<string>& args) {
				return nullptr;
			});
			GameState* mm = new MainMenu(new StateStorage());
			c.add_overload(3, [&mm](const vector<string>& args) {
				Assert::AreEqual(string("a"), args[0], L"Incorrect argument (0).");
				Assert::AreEqual(string("hello world"), args[1], L"Incorrect argument (1).");
				Assert::AreEqual(string("11111"), args[2], L"Incorrect argument (2).");
				return mm;
			});
			vector<string> args;
			CommandResult cr = c(args);
			if (cr.success() == SuccessState::Success) {
				if (cr.result() != nullptr) {
					delete mm;
					Assert::Fail(L"Correct value was not returned (0).");
				}
			}
			else {
				delete mm;
				Assert::Fail(L"Correct overload was not called (0).");
			}
			args.push_back("a");
			args.push_back("hello world");
			args.push_back("11111");
			cr = c(args);
			if (cr.success() == SuccessState::Success) {
				if (cr.result() != mm) {
					delete mm;
					Assert::Fail(L"Correct value was not returned (3).");
				}
			}
			else {
				delete mm;
				Assert::Fail(L"Correct overload was not called (3).");
			}
			args.clear();
			args.push_back("y");
			cr = c(args);
			if (cr.success() != SuccessState::NoValidOverload) {
				delete mm;
				Assert::Fail(L"Invalid overload did not set SuccessState to NoValidOverload (1).");
			}
			delete mm;
		};
	};
}