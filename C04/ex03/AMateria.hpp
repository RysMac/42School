#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>
#include "ICharacter.hpp"

class AMateria
{
protected:

public:
    AMateria(std::string const & type);

    std::string const & getType() const;  //Returns the materia type

    virtual AMateria*   clone() const = 0; // pure virtual function
    virtual void        use(ICharacter& target);

};


#endif