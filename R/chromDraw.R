# This file was generated by Rcpp::compileAttributes
# Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393


#' Main chromDraw function. This R function calls the main C++ function.
#' 
#' @param argc count of the input parameters.
#' @param argv vector with the input parameters strings.
#' @return return exit state.
chromDraw <- function(argc, argv)
{
  withRestarts(invokeRestart("callFce", argc, argv), callFce = function(argc, argv) {
    .Call('chromDraw_main_chromDraw', PACKAGE = 'chromDraw', argc, argv)
  })
}



