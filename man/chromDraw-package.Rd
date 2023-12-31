\name{chromDraw-package}
\alias{chromDraw-package}
\docType{package}
\title{
chromDraw - simple karyotype visualization tool.
}
\description{
ChromDraw is a R package for drawing the schemes of karyotype(s) in the linear and circular fashion. It is possible to visualized cytogenetic marsk on the chromosomes. This tool has own input data format. Input data can be imported from the GenomicRanges data structure. This package can visualized the data in the BED file format. Here is requirement on to the first nine fields of the BED format. Output files format are *.eps and *.svg.
}
\details{
\tabular{ll}{
Package: \tab chromDraw\cr
Type: \tab Package\cr
Date: \tab 2015-12-12\cr
License: \tab GPL-3 \cr
License: \tab LGPL | library Board \cr
}
This package has only one function with two parameters, such as main function in C. First parameter ARGC is a count of input parameters and second parameter ARGV is vector contain calling parameters.  
Example:
chromDraw(argc=5, argv=c("chromDraw", "-c", "/home/user/Documents/colors.txt", "-d", "/home/user/Documents/input_data.txt"))

First string in vector with arguments must be  package name. The others strings in vector are parameter string and string with parameter value. As shown in the example.

}
\author{
Jan Janecka, Ing. Mgr.
CEITEC MU
Masaryk University
Kamenice 5, Building A26
CZ-625 00, Brno
Czech Republic
tel.: 549 49 8190

Email: jan.janecka@ceitec.muni.cz
}
\references{
LibBoard: A vector graphics C++ library (Version 0.9.0). GREYC laboratory. [Software]. \url{http://libboard.sourceforge.net/}. [accessed Sept. 2014]. 
}
%~~ Optionally other standard keywords, one per line, from file ~~
%~~ KEYWORDS in the R documentation directory ~~
\keyword{ package, libBoard, getopt, Rcpp, chromosome visualization, karyotype visualization, comparing karyotypes }
\seealso{
%~~ Optional links to other man pages, e.g. ~~
\code{\link{chromDraw}}
\code{\link{main_chromDraw}}
}
\examples{
OUTPUTPATH = file.path(getwd());
INPUTPATH = system.file('extdata','Ack_and_Stenopetalum_nutans.txt', package ='chromDraw')
COLORPATH = system.file('extdata','default_colors.txt', package ='chromDraw')
chromDraw(argc=7, argv=c("chromDraw", "-c", COLORPATH, "-d", INPUTPATH, "-o", OUTPUTPATH));
}
