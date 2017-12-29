#pragma once

#include <exception>


class bad_matrix : public std::exception {

};

class bad_matrix_row : public std::exception {

};

class bad_matrix_col : public std::exception {

};

class bad_matrix_operation : public std::exception {

};
