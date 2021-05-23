#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stack>
#include <chrono>
#include "Matrix.hpp"
#include <eigen3/Eigen/Dense>

/**
 * time checks mult and add on eigen matrix and mathlib matrix.
 * if an error occure prints an informative msg and exits with failure,
 * otherwise prints the time checks and exits successfully.
 * */
int main(int argc, char *argv[])
    {
        if(argc == 2)
        {
            try {
                char *res;
                long arg = strtol(argv[1], &res, 10);
                if (arg > 0 && arg <= 500 && strcmp(res, "") == 0) {
                    auto n = (unsigned int) arg;
                    std::cout << "size " << n << std::endl;

                    std::stack<std::chrono::time_point<std::chrono::system_clock>> tictoc_stack;
                    std::chrono::duration<double> elapsed_seconds{};

                    Eigen::MatrixXd Ea, Em;
                    Matrix<int> Ma, Mm;
                    Eigen::MatrixXd A = Eigen::MatrixXd::Random(n, n);
                    Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
                    std::vector<int> cells(n * n, 1);
                    Matrix<int> C = Matrix<int>(n, n, cells);

                    //Eigen:
                    tictoc_stack.push(std::chrono::system_clock::now()); //tic
                    Em = A * B;
                    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
                    std::cout << "eigen mult " << elapsed_seconds.count() << std::endl; // tock
                    tictoc_stack.pop();
                    tictoc_stack.push(std::chrono::system_clock::now()); //tic
                    Ea = B + A;
                    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
                    std::cout << "eigen add " << elapsed_seconds.count() << std::endl; // tock
                    tictoc_stack.pop();

                    //Matlib:
                    tictoc_stack.push(std::chrono::system_clock::now()); //tic
                    Mm = C * C;
                    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
                    std::cout << "matlib mult " << elapsed_seconds.count() << std::endl; // tock
                    tictoc_stack.pop();
                    tictoc_stack.push(std::chrono::system_clock::now()); //tic
                    Ma = C + C;
                    elapsed_seconds = std::chrono::system_clock::now() - tictoc_stack.top();
                    std::cout << "matlib add " << elapsed_seconds.count() << std::endl; // tock
                    tictoc_stack.pop();
                    return 0;
                }
            }
            catch (std::exception const& e)
            {
                std::cerr << e.what() << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        std::cerr << "Usage: TimeChecker <param1> (where <param1> is an 0 < int <= 500)" << std::endl;
        exit(EXIT_FAILURE);
    }



