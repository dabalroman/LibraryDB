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

void Record::setName(const string &name_) {
	Record::name = name_;
}

void Record::setDescription(const string &description_) {
	Record::description = description_;
}

void Record::setSignature(const string &signature_) {
	Record::signature = signature_;
}

void Record::setAuthor(const string &author_) {
	Record::author = author_;
}

const string &Record::getName() const {
	return name;
}

const string &Record::getDescription() const {
	return description;
}

const string &Record::getSignature() const {
	return signature;
}

const string &Record::getAuthor() const {
	return author;
}

const Record::State &Record::getState() const {
	return state;
}

void Record::setState(State s) {
	Record::state = s;
}

