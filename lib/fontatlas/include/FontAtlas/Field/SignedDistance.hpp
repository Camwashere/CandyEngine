
#pragma once

namespace msdfgen {

/// Represents a signed distance and alignment, which together can be compared to uniquely determine the closest edge segment.
class SignedDistance {

public:
    float distance;
    float dot;

    SignedDistance();
    SignedDistance(float dist, float d);

    friend bool operator<(SignedDistance a, SignedDistance b);
    friend bool operator>(SignedDistance a, SignedDistance b);
    friend bool operator<=(SignedDistance a, SignedDistance b);
    friend bool operator>=(SignedDistance a, SignedDistance b);

};

}
