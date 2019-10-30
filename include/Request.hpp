#if !defined(CMO_REQUEST)
#define CMO_REQUEST

#include <vector>

class Request
{
public:
    double created_at;
    int source;
    int num;
    double received_in;
    double done_in;
    Request(double generationTime,
            int sourceNumber,
            int num_) : source(sourceNumber),
                        created_at(generationTime),
                        received_in(-1),
                        done_in(-1),
                        num(num_){};
};

struct StepData
{
    // [ 1 , 2, -1 , 1 ] - номер заявки, -1 её отсутствие
    std::vector<Request *> sourceData;
    std::vector<Request *> bufferData;
    std::vector<Request *> deviceData;
    double timestamp;

    StepData(
        std::vector<Request *> sourceData_,
        std::vector<Request *> bufferData_,
        std::vector<Request *> deviceData_,
        double timestamp_) : sourceData(sourceData_),
                             bufferData(bufferData_),
                             deviceData(deviceData_),
                             timestamp(timestamp_){};
};

#endif // CMO_REQUEST
