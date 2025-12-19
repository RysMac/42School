#include <iostream>

class Contact {
private:
	std::string	first_name;
	std::string	last_name;
	std::string	nickname;
	std::string	phone_nbr;
	std::string	darkest_secret;
public:
	std::string	get_first_name() {
		return first_name;
	}
	std::string	get_last_name() {
		return last_name;
	}
	std::string	get_nickname() {
		return nickname;
	}
	std::string	get_phone_nbr() {
		return phone_nbr;
	}
	std::string	get_secret() {
		return darkest_secret;
	}
	void	set_first_name(std::string first_name) {
		this->first_name = first_name;
	}
	void	set_last_name(std::string last_name) {
		this->last_name = last_name;
	}
	void	set_nickname(std::string nickname) {
		this->nickname = nickname;
	}
	void	set_phone_nbr(std::string phone_nbr) {
		this->phone_nbr = phone_nbr;
	}
	void	set_secret(std::string darkest_secret) {
		this->darkest_secret = darkest_secret;
	}
};
