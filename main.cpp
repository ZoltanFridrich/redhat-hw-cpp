#include <iostream>
#include <queue>
#include <sstream>

using num_t = double;

struct Item {
    num_t value;
    size_t priority;
    size_t counter;
};

auto cmp = [](const Item &lhs, const Item &rhs) {
    return lhs.priority == rhs.priority ? lhs.counter > rhs.counter : lhs.priority < rhs.priority;
};

using buffer = typename std::priority_queue<Item, std::vector<Item>, decltype(cmp)>; 

enum class InputType { unknown, push, print, get, exit };

InputType parseInput(std::string &&str, Item &item) {
    if (str == "exit") return InputType::exit;
    if (str == "print") return InputType::print;
    if (str == "get") return InputType::get;
    std::stringstream ss(str);
    char c;
    if ((ss >> item.value).get(c) >> item.priority && c == ':') {
	static size_t counter = 0;
	item.counter = ++counter;
	return InputType::push;
    }
    return InputType::unknown;
}

inline void printTop(const buffer &buf) {
    std::cout << buf.top().value << ':' << buf.top().priority << std::endl;
}

int main() {
    buffer buf(cmp);
    for (std::string input; std::getline(std::cin, input);) {
	Item item;
	switch (parseInput(std::move(input), item)) {
	case InputType::push:
	    buf.push(item);
	    break;
        case InputType::print:
	    while (!buf.empty()) {
		printTop(buf);
		buf.pop();
	    }
	    break;
	case InputType::get:
	    if (!buf.empty()) printTop(buf);
	    break;
	case InputType::exit:
	    return 0;
	case InputType::unknown:
	    std::cerr << "Unknown type of input!" << std::endl;
	    break;
	}
    }
    return 0;
}
