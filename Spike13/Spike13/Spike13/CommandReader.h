#pragma once

#include <set>
#include <list>
#include <stack>
#include <sstream>
#include "Object.h"
#include "LineResult.h"

class CommandReader : public Object {
private:
	class StringReader : public Object {
	private:
		std::string _str;
		std::stack<std::size_t> _lastIndices;
		std::size_t _index;
		bool is_valid(const char& c) const;
		std::string read(const std::set<char>& beginOn,const std::set<char>& breakOn,bool begun);
		std::string read(const std::set<char>& beginOn,const std::set<char>& breakOn);
		std::string read(const std::set<char>& breakOn);
		std::string read();
	public:
		StringReader(std::string str);
		virtual ~StringReader();
		virtual std::string type_name() const override;
		char current_char() const;
		bool in_range() const;
		void next();
		std::string read_identifier();
		std::string read_rest();
		std::string read_c_string();
		int read_number();
		std::list<std::string> read_c_string_list();
		void rollback();
	};
	class CommandComponent : public Object {
	private:
		std::string _contents;
		bool _whitespaceAfter;
	public:
		CommandComponent(std::string contents,bool whitespaceAfter);
		virtual ~CommandComponent();
		virtual std::string type_name() const override;
		std::string contents() const;
		bool whitespace_after() const;
	};
	std::stringstream _input;
	std::string regex_escape_component(const std::string& str,char c);
	std::string regex_escape(std::string str);
	StringReader read_line();
	LineResult parse_line(const std::set<std::string>& validIds,int l);
public:
	CommandReader();
	virtual ~CommandReader();
	virtual std::string type_name() const override;
	std::list<LineResult> read(std::string file,const std::set<std::string>& validIds);
};