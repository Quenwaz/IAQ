#include <cstddef>
#include <cstdio>
#include "iaq/solve/byte_alignment.hpp"


size_t iaq::solve::bytealign::ByteAlign::operator()(Situation situation) const
{
    switch (situation)
    {
    case kS1:
        return sizeof(testdata::Struct1);
    case kS2:
        return sizeof(testdata::Struct2);
    case kS3:
        return sizeof(testdata::Struct3);
    case kS4:
        return sizeof(testdata::Struct4);
    case kS5:
        return sizeof(testdata::Struct5);
    case kS6:
        {
            testdata::Struct6 t;
            fprintf(stderr, "ch:%p integer:%p shorttype:%p point:%p doubletype:%p\n", &t.ch, &t.integer, &t.shorttype,&t.point, &t.doubletype);
            return sizeof(testdata::Struct6);
        }
    case kS7:
        {
            testdata::Struct7 t;
            fprintf(stderr, "ch:%p integer:%p shorttype:%p doubletype:%p\n", &t.ch, &t.integer, &t.shorttype, &t.doubletype);
            return sizeof(testdata::Struct7);
        }
    case kS8:
        return sizeof(testdata::Struct8);
    default:
        break;
    }
    return 0;
}

