/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysetiawa <ysetiawa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 23:53:55 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/14 16:19:56 by ysetiawa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MateriaSource.hpp"

MateriaSource::MateriaSource() {
    for (int i = 0; i < 4; ++i)
        templates[i] = NULL;
    std::cout << "Materia Sources are created (default)." << std::endl;
}

MateriaSource::MateriaSource(const MateriaSource& other)
{
    for (int i = 0; i < 4; ++i)
    {
        if (other.templates[i])
            templates[i] = other.templates[i]->clone();
        else
            templates[i] = NULL;
    }
    std::cout << "Materia Sources are copied." << std::endl;
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
    if (this != &other)
    {
        for (int i = 0; i < 4; ++i)
        {
            delete templates[i];
            if (other.templates[i])
                templates[i] = other.templates[i]->clone();
            else
                templates[i] = NULL;
        }
    }
    std::cout << "Materia Sources are assigned." << std::endl;
    return *this;
}

MateriaSource::~MateriaSource()
{
    for (int i = 0; i < 4; ++i)
        delete templates[i];  // Free the memory
    std::cout << "Materia Sources are destroyed." << std::endl;
}

void MateriaSource::learnMateria(AMateria* m)
{
    for (int i = 0; i < 4; ++i)
    {
        if (!templates[i])
        {
            templates[i] = m->clone();  // Ensure you clone the Materia here
            break;
        }
    }
}

AMateria* MateriaSource::createMateria(std::string const & type)
{
    for (int i = 0; i < 4; ++i)
    {
        if (templates[i] && templates[i]->getType() == type)
            return templates[i]->clone();
    }
    return NULL;
}
