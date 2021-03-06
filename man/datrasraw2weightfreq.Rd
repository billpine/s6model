% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/datras.R
\name{datrasraw2weightfreq}
\alias{datrasraw2weightfreq}
\title{Convert a DATRASraw object to weight frequency data.frame}
\usage{
datrasraw2weightfreq(datr, a = 0.01, b = 3, estWL = FALSE,
  verbose = TRUE)
}
\arguments{
\item{datr}{DATRASraw object}

\item{a}{numeric weight-length relationship, parameter a, see Details}

\item{b}{numeric, weight-length relationship, parameter b, see Details}

\item{estWL}{logical, if TRUE and available information about weight is available, the weight-length relationship is fitted}

\item{verbose}{logical, if TRUE it shows information about the fitted weight length parameters and the output \code{data.frame}}
}
\value{
data.frame with columns Weight, Freq containing the weight frequencies of the input data
}
\description{
The length information of a DATRASraw object is transformed to weight and the weight frequency is returned as \code{data.frame}
}
\details{
The weight-length relationship has the form $W = aL^b$
}
\author{
alko
}
