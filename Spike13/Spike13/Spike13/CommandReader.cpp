#include "CommandReader.h"
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include "StringUtils.h"

using namespace std;
using namespace StringUtils;

bool CommandReader::StringReader::is_valid(const char& c) const {
	return c != '\0';
}
string CommandReader::StringReader::read(const set<char>& beginOn,const set<char>& breakOn,bool begun) {
	string res;
	if (in_range()) {
		bool escapeNext = false;
		char c;
		do {
			c = current_char();
			next();
			if (escapeNext) {
				if (begun) {
					res += c;
				}
				escapeNext = false;
			} else if (begun && breakOn.find(c) != breakOn.end()) {
				break;
			} else if (c == '\\') {
				escapeNext = true;
			} else if (begun) {
				res += c;
			} else if (beginOn.find(c) != beginOn.end()) {
				begun = true;
			}
		} while (in_range());
	}
	return res;
}
string CommandReader::StringReader::read(const set<char>& beginOn,const set<char>& breakOn) {
	return read(beginOn,breakOn,false);
}
string CommandReader::StringReader::read(const set<char>& breakOn) {
	set<char> empty;
	return read(empty,breakOn,true);
}
string CommandReader::StringReader::read() {
	set<char> empty;
	return read(empty,empty,true);
}
CommandReader::StringReader::StringReader(string str) : _str(str), _index(0) {
}
CommandReader::StringReader::~StringReader() {
}
string CommandReader::StringReader::type_name() const {
	return "CommandReader::StringReader";
}
char CommandReader::StringReader::current_char() const {
	char res = '\0';
	if (in_range()) {
		res = _str[_index];
	}
	return res;
}
bool CommandReader::StringReader::in_range() const {
	return _index >= 0 && _index < _str.length();
}
void CommandReader::StringReader::next() {
	_lastIndices.push(_index);
	char c;
	if (in_range()) {
		do {
			c = _str[++_index];
		} while (in_range() && is_whitespace(c));
	}
}
string CommandReader::StringReader::read_identifier() {
	set<char> equals;
	equals.insert('=');
	return read(equals);
}
string CommandReader::StringReader::read_rest() {
	return read();
}
string CommandReader::StringReader::read_c_string() {
	set<char> quotes;
	quotes.insert('\"');
	return read(quotes,quotes);
}
list<string> CommandReader::StringReader::read_c_string_list() {
	set<char> open;
	open.insert('[');
	set<char> close;
	close.insert(']');
	string collection = read(open,close);
	StringReader r(collection);
	list<string> res;
	string toAdd = r.read_c_string();
	while (r.in_range()) {
		res.push_back(toAdd);
		toAdd = r.read_c_string();
	}
	if (toAdd.length() != 0) {
		res.push_back(toAdd);
	}
	return res;
}
int CommandReader::StringReader::read_number() {
	set<char> open;
	open.insert('{');
	set<char> close;
	close.insert('}');
	string collection = read(open,close);
	return atoi(collection.c_str());
}
void CommandReader::StringReader::rollback() {
	if (_lastIndices.empty()) {
		throw new runtime_error("Cannot rollback before the first index.");
	}
	_index = _lastIndices.top();
	_lastIndices.pop();
}

CommandReader::CommandComponent::CommandComponent(string contents,bool whitespaceAfter) : _contents(contents), _whitespaceAfter(whitespaceAfter) {
}
CommandReader::CommandComponent::~CommandComponent() {
}
string CommandReader::CommandComponent::type_name() const {
	return "CommandReader::CommandComponent";
}
string CommandReader::CommandComponent::contents() const {
	return _contents;
}
bool CommandReader::CommandComponent::whitespace_after() const {
	return _whitespaceAfter;
}

string CommandReader::regex_escape_component(const string& str,char c) {
	string from;
	from += c;
	string to = "\\";
	to += c;
	return substring_replace(str,from,to);
}
string CommandReader::regex_escape(string str) {
	str = regex_escape_component(str,'\\');
	str = regex_escape_component(str,'.');
	str = regex_escape_component(str,'^');
	str = regex_escape_component(str,'$');
	str = regex_escape_component(str,'|');
	str = regex_escape_component(str,'(');
	str = regex_escape_component(str,')');
	str = regex_escape_component(str,'[');
	str = regex_escape_component(str,']');
	str = regex_escape_component(str,'{');
	str = regex_escape_component(str,'}');
	str = regex_escape_component(str,'*');
	str = regex_escape_component(str,'+');
	str = regex_escape_component(str,'?');
	return str;
}
CommandReader::StringReader CommandReader::read_line() {
	string res;
	char c;
	_input.get(c);
	while (c != '\n' && _input.good()) {
		res += c;
		_input.get(c);
	}
	return StringReader(res);
}
LineResult CommandReader::parse_line(const set<string>& validIds,int l) {
	StringReader line = read_line();
	LineResult res;
	string id = line.read_identifier();
	res.valid = id.length() != 0;
	if (res.valid) {
		res.valid = validIds.find(id) != validIds.end();
		if (res.valid) {
			string expr = line.read_rest();
			res.valid = expr.length() != 0;
			if (res.valid) {
				list<CommandComponent> components;
				components.push_back(CommandComponent("^",true));
				line = StringReader(expr);
				bool cnt = res.valid;
				while (cnt) {
					// Build a regex
					char c = line.current_char();
					if (c == '\"') {
						string literal = regex_escape(line.read_c_string());
						c = line.current_char();
						if (c == '?') {
							// Optional string
							components.push_back(CommandComponent("(?:",true));
							components.push_back(CommandComponent(literal,true));
							components.push_back(CommandComponent(")?",false));
						} else {
							// Required string
							line.rollback();
							components.push_back(CommandComponent(literal,true));
						}
						line.next();
						cnt = line.in_range();
					} else if (c == '[') {
						// String group
						list<string> group = line.read_c_string_list();
						components.push_back(CommandComponent("(?:",true));
						components.push_back(CommandComponent("(?:",false));
						string literal;
						bool isFirst = true;
						for (list<string>::const_iterator i = group.cbegin(); i != group.cend(); ++i) {
							literal = regex_escape(*i);
							if (isFirst) {
								isFirst = false;
							} else {
								components.push_back(CommandComponent("|",false));
							}
							components.push_back(CommandComponent(literal,false));
						}
						components.push_back(CommandComponent(")",false));
						if (line.current_char() == '?') {
							// Optional string group
							components.push_back(CommandComponent("?",true));
						} else {
							// Required string group
							components.push_back(CommandComponent("",true));
							line.rollback();
						}
						components.push_back(CommandComponent(")",false));
						line.next();
						cnt = line.in_range();
					} else if (c == '{') {
						// Argument gap
						// \s*?(\"[\s\S]*?\"|\S+?) n times
						int size = line.read_number();
						for (int i = 0; i < size; ++i) {
							components.push_back(CommandComponent("(?:",true));
							components.push_back(CommandComponent("(\"[\\s\\S]*?\"|\\S+?)",true));
							components.push_back(CommandComponent(")",false));
						}
					} else {
						// Invalid character found
						res.valid = false;
						res.error = "Command body not in correct format :" + to_string(l);
					}
				}
				if (!res.has_error()) {
					res.id = id;
					for (list<CommandComponent>::const_iterator i = components.cbegin(); i != components.cend(); ++i) {
						res.regex += i->contents();
						if (i->whitespace_after()) {
							res.regex += "\\s*?";
						}
					}
				}
			} else {
				res.error = "No command body specified :" + to_string(l);
			}
		} else {
			res.error = "Specified command I.D. (" + id + ") is not a valid I.D. :" + to_string(l);
		}
	}
	return res;
}
CommandReader::CommandReader() {
}
CommandReader::~CommandReader() {
}
string CommandReader::type_name() const {
	return "CommandReader";
}
list<LineResult> CommandReader::read(string file,const set<string>& validIds) {
	_input.clear();
	_input << fstream(file).rdbuf();
	list<LineResult> res;
	LineResult lr = parse_line(validIds,1);
	int line = 1;
	while (lr.valid) {
		res.push_back(lr);
		lr = parse_line(validIds,++line);
	}
	if (lr.has_error()) {
		throw new runtime_error(lr.error);
	}
	return res;
}
