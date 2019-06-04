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

const int Record::getIntState() const {
	return static_cast<int>(state);
}

const Record::State Record::getState() const {
	return state;
}

void Record::setState(const State &state_) {
	state = state_;
}

bool Record::compareByName(Record *a, Record *b) {
	return (a->name.compare(b->name) < 0);
}

bool Record::compareByAuthor(Record *a, Record *b) {
	return (a->author.compare(b->author) < 0);
}

bool Record::compareBySignature(Record *a, Record *b) {
	return (a->signature.compare(b->signature) < 0);
}

bool Record::compareByState(Record *a, Record *b) {
	return (a->getIntState() < b->getIntState());
}

bool Record::matchString(const string &s) {
	return cropString(name, s.length()) == s
	       || cropString(author, s.length()) == s
	       || cropString(signature, s.length()) == s;
}



