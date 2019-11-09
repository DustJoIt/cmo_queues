#if !defined(CMO_SOURCE_HPP)
#define CMO_SOURCE_HPP

#include "Request.hpp"
#include "StatManager.hpp"

class Source
{
private:
    int sourceNumber;
    int currNum;
    double lambda;
public:
    Request *current;
    Source(StatManager *manager, int sourceNumber, double lambda);
    Request *emitRequest();
    void generateRequest();
};

#endif // CMO_SOURCE_HPP
