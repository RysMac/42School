#include "Contact.hpp"

std::string	Contact::get_first_name() const { return first_name; }
std::string	Contact::get_last_name() const { return last_name; }
std::string	Contact::get_nickname() const {return nickname; }
std::string	Contact::get_phone_nbr() const { return phone_nbr; }
std::string	Contact::get_secret() const { return darkest_secret; }

void	Contact::set_first_name(std::string first_name) { this->first_name = first_name; }
void	Contact::set_last_name(std::string last_name) { this->last_name = last_name; }
void	Contact::set_nickname(std::string nickname) { this->nickname = nickname; }
void	Contact::set_phone_nbr(std::string phone_nbr) { this->phone_nbr = phone_nbr; }
void	Contact::set_secret(std::string darkest_secret) { this->darkest_secret = darkest_secret; }