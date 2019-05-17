//
// Created by rd on 16/05/2019.
//

#include "Record.hpp"

Record::Record(const Record &record) {
	this->name = record.name;
	this->signature = record.signature;
	this->author = record.author;
	this->description = record.description;
	this->state = record.state;
}

const int Record::getState() const {
	return static_cast<int>(state);
}

void Record::setState(const int &state_) {
	state = static_cast<State>(state);
}

