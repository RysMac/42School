#include <string>

class	Harl {
private:
	void	debug( void ) const;
	void	info( void ) const;
	void	warning( void ) const;
	void	error( void ) const;
public:
	void		complain(const std::string& level) const;
	int			levelToIndex(const std::string& level) const;
};
