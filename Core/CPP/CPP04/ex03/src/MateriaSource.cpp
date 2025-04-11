/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yocelynnns <yocelynnns@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 23:53:55 by yocelynnns        #+#    #+#             */
/*   Updated: 2025/04/12 00:14:08 by yocelynnns       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource() {
    for (int i = 0; i < 4; ++i) templates[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource& other) {
    for (int i = 0; i < 4; ++i)
        templates[i] = other.templates[i] ? other.templates[i]->clone() : NULL;
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other) {
    if (this != &other) {
        for (int i = 0; i < 4; ++i) {
            delete templates[i];
            templates[i] = other.templates[i] ? other.templates[i]->clone() : NULL;
        }
    }
    return *this;
}

MateriaSource::~MateriaSource() {
    for (int i = 0; i < 4; ++i) {
        delete templates[i];  // Free the memory
    }
}

void MateriaSource::learnMateria(AMateria* m) {
    for (int i = 0; i < 4; ++i) {
        if (!templates[i]) {
            templates[i] = m->clone();  // Ensure you clone the Materia here
            break;
        }
    }
}

AMateria* MateriaSource::createMateria(std::string const & type) {
    for (int i = 0; i < 4; ++i) {
        if (templates[i] && templates[i]->getType() == type)
            return templates[i]->clone();
    }
    return NULL;
}
