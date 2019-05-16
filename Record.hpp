//
// Created by rd on 16/05/2019.
//

#ifndef LIBRARYDB_RECORD_HPP
#define LIBRARYDB_RECORD_HPP

#include <string>

using namespace std;

class Record {
public:
	enum class State : short {
		Lend = 0,
		Available = 1,
		Unavailable = 2,
	};

protected:
	string name, description, signature, author;
	Record::State state;

public:

	/***
	 * Constructor
	 * @param name
	 * @param author
	 * @param description
	 * @param signature
	 */
	Record(string name, string author, string description = "", string signature = "")
			: name(std::move(name)),
			  author(std::move(author)),
			  description(std::move(description)),
			  signature(std::move(signature)),
			  state(State::Available) {};

	/***
	 * Copy constructor
	 * @param record
	 */
	Record(const Record &record);

	const State &getState() const;

	const string &getName() const;

	const string &getDescription() const;

	const string &getSignature() const;

	const string &getAuthor() const;

	void setState(State state);

	void setName(const string &name_);

	void setAuthor(const string &author_);

	void setSignature(const string &signature_);

	void setDescription(const string &description_);
};


#endif //LIBRARYDB_RECORD_HPP
