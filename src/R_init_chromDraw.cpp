/*
* Name: R_init_chromDraw.cpp
* Description: Registration methods.
* Author: Jan Janecka, ing  c 2014
* Contact: jan.janecka@ceitec.muni.cz
*/

#include <R_ext/Rdynload.h>
#include <Rcpp.h>

int main_chromDraw(int argc, Rcpp::StringVector argv);


// registration methods with R
static const R_CallMethodDef callMethods[] = {
  {"main_chromDraw", (DL_FUNC) &main_chromDraw,2},
  {NULL, NULL, 0}
};


void R_init_chromDraw(DllInfo * info)
{
    R_registerRoutines(info, NULL, callMethods, NULL, NULL);
}
