//
// Created by rd on 16/05/2019.
//

#ifndef LIBRARYDB_RECORD_HPP
#define LIBRARYDB_RECORD_HPP

#include <string>

using namespace std;

/**
 * Record data class
 */
class Record {
public:
	enum class State : short {
		Lend = 0,
		Available = 1,
		Unavailable = 2,
	};

	string name, description, signature, author;
	Record::State state;

public:

	/***
	 * Constructor
	 * @param name Book name
	 * @param author Author full name
	 * @param description Description
	 * @param signature Unique book signature
	 */
	Record(string name, string author, string description = "", string signature = "", State state = State::Available)
			: name(std::move(name)),
			  author(std::move(author)),
			  description(std::move(description)),
			  signature(std::move(signature)),
			  state(state) {};

	/***
	 * Copy constructor
	 * @param record Record object to copy
	 */
	Record(const Record &record);

	/**
	 * Get state as int
	 * @return state State as int
	 */
	const int getState() const;

	/**
	 * Set state from int
	 * @param state State as int
	 */
	void setState(const int &state);
};


#endif //LIBRARYDB_RECORD_HPP
