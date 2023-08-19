#include <emscripten.h>

#include <vector>
#include <iostream>
#include <amgcl/backend/builtin.hpp>
#include <amgcl/adapter/crs_tuple.hpp>
#include <amgcl/make_solver.hpp>
#include <amgcl/amg.hpp>
#include <amgcl/coarsening/smoothed_aggregation.hpp>
#include <amgcl/relaxation/spai0.hpp>
#include <amgcl/solver/bicgstab.hpp>

/**** PROTOTYPE ***/
extern "C" void EMSCRIPTEN_KEEPALIVE solve(int , int , int* ,int*,double*, double* ,double*,double ,int , double*,double* , int* );

/*****************/

/**
 * solve linear sysmtem quations expressed as Ax=rhs 
 * @param {int} rows number of rows of matrix as equal as colums of matrix and right hand vector
 * @param {int} nnz number of non zero elements in system matrix
 * @param {int*} Ptr 
 * @param {int*} Col 
 * @param {double*} Val
 * @param {dobule*} Rhs 
 * @param {double*} iniX initial values for solver 
 * @param {double} tolerance tolerance for solver 
 * @param {int} maxIteration maximum iteration number for solver 
 * @param {double*} x values returned from solver after solving (result)
 * @param {double*} err resesdual at final step (result)
 * @param {double*} iteration at final step (result)
 */

void solve(int rows,int nnz, int  Ptr[], int Col[],double Val[], double Rhs[],double iniX[],
           double tolerance,int maxIteration, double X[],double* err, int* iteration ){

 
  std::vector<ptrdiff_t> ptr(rows+1), col(nnz);
  std::vector<double> val(nnz), rhs(rows);
  std::vector<double> x(rows);

  for (int i = 0; i < rows; ++i) {
    rhs[i] = Rhs[i];
    x[i] = X[i];
  }
  for (int i = 0; i < rows+1; ++i) {
    ptr[i] = Ptr[i];
  } 
  for (int i = 0; i < nnz; ++i) {
    val[i] = Val[i];
    col[i] = Col[i];
  } 

  auto A = std::tie(rows, ptr, col, val);
//  // Compose the solver type
//  //   the solver backend:
  typedef amgcl::backend::builtin<double> SBackend;
//  
  typedef amgcl::backend::builtin<double> PBackend;
//  
  typedef amgcl::make_solver<
      amgcl::amg<
          PBackend,
          amgcl::coarsening::smoothed_aggregation,
          amgcl::relaxation::spai0
          >,
      amgcl::solver::bicgstab<SBackend>
      > Solver;
  
  Solver::params prm;
  prm.solver.tol = tolerance;
  prm.solver.maxiter = maxIteration;
 
//  // Initialize the solver with the system matrix:
  Solver solve(A, prm);
//     // Show the mini-report on the constructed solver:
//  
//  // Solve the system with the zero initial approximation:
//
  int iters;
  double error;
  
  std::tie(iters, error) = solve(A, rhs, x);
  //err = &error;
  err[0]=error;
  iteration[0] =iters;
  for(int i = 0; i != x.size(); ++i) {      // 全要素に対するループ
    X[i] = x[i];
  }
}

