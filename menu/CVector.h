#pragma once

template <class T>
class CVector {

private:
	struct Item {
		T value;
		Item* next;
	};

	Item* head = nullptr;
	Item* tail = nullptr;

	int length = 0;

public:
	void push_back(T value) {
		auto newItem = new Item(value, nullptr);

		if (head == nullptr) {
			head = newItem;
			tail = head;
		}
		else {
			tail->next = newItem;
			tail = newItem;
		}

		length++;
	}

	T& itemAt(int index) {
		if (length > 0 && index < length) {
			Item* curItem = head;
			int i = 0;
			while (curItem != nullptr && i < length) {
				i++;
				curItem = curItem->next;
			}
			return curItem->value;
		}
		else throw "No such element";
	}

	T& operator[](int index) {
		return itemAt(index);
	}
};