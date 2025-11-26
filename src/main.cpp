#include"all.hpp"

void action_1(Taskmanager &A) {
	while (1) {
		if (A.out != 0) {
			std::lock_guard<mutex> lock(mtx);
			cout << "out为：" << A.out << endl;
			A.out = 0;
			cv.notify_one();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}


void action_2(Taskmanager &A) {
	mutex all;
	while (1) {
		std::string instruction;
		cout << "请输入指令" << endl;
		std::cin >> instruction;
		if (instruction == "add") {
			A.add();
		}
		else if (instruction == "pop") {
			A.pop();
		}
		else {
			std::unique_lock<mutex> outputlock(all);
			A.callbackuse();
			cv.wait(outputlock);
		}
	}
}


int main() {
	Taskmanager ALL;
	ALL.b_n.reserve(10000);
	thread at(action_1, std::ref(ALL));
	thread ar(action_2, std::ref(ALL));
	at.join();
	ar.join();
	return 0;
}