#ifndef ABSTRACTLINEARMOVIESOURCE_H
#define ABSTRACTLINEARMOVIESOURCE_H

#include "AbstractImageSource.h"
#include "AbstractPauseable.h"

class AbstractLinearMovieSource : public AbstractImageSource, public AbstractPauseable {};

#endif // ABSTRACTLINEARMOVIESOURCE_H
