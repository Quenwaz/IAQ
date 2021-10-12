#ifndef _H_BYTE_ALIGNMENT_INCLUDED__
#define _H_BYTE_ALIGNMENT_INCLUDED__
#include <cstddef>
#include <cstdint>
#include "iaq/iaq_defs.hpp"


namespace iaq::solve::bytealign
{
    enum Situation{
        kS1,
        kS2,
        kS3,
        kS4,
        kS5,
        kS6,
        kS7,
        kS8,
        kS9,
        kS10
    };

    namespace testdata{
        /*
        [x] [ ] [ ] [ ]   ch
        [x] [x] [x] [x]   integer
        */
        struct Struct1{
            char ch;
            int integer;
        };

        /*
        [x] [ ] [ ] [ ]   ch1
        [x] [x] [x] [x]   integer
        [x] [ ] [ ] [ ]   ch2
        */
        struct Struct2{
            char ch1;
            int integer;
            char ch2;
        };

        /*
        [x] [x] [x] [x]   ch[4]
        [x] [x] [x] [x]   ch[4]
        [x] [x] [ ] [ ]   ch[2]
        [x] [x] [x] [x]   integer
        */
        struct Struct3{
            char ch[10];
            int integer;
        };

        /*
        [x] [x] [x] [x] [x] [ ] [ ] [ ]   ch1~ch5
        [x] [x] [x] [x] [x] [x] [x] [x]   integer & floattype
        [x] [x] [x] [x] [x] [x] [x] [x]   doubletype
        */
        struct Struct4{
            char ch1;
            char ch2;
            char ch3;
            char ch4;
            char ch5;
            int integer;
            float floattype;
            double doubletype;
        };

        /*
        [x] [x] [x] [x] [x] [ ] [ ] [ ]   ch1~ch5
        [x] [x] [x] [x] [ ] [ ] [ ] [ ]   floattype
        [x] [x] [x] [x] [x] [x] [x] [x]   doubletype
        [x] [x] [x] [x] [ ] [ ] [ ] [ ]   integer
        */
        struct Struct5{
            char ch[5];
            float floattype;
            double doubletype;
            int integer;
        };

        /*
        [x] [ ] [ ] [ ] [x] [x] [x] [x]   ch & integer
        [x] [x] [ ] [ ] [ ] [ ] [ ] [ ]   shorttype
        [x] [x] [x] [x] [x] [x] [x] [x]   point
        [x] [x] [x] [x] [x] [x] [x] [x]   doubletype
        */
        struct Struct6{
            char ch;
            int integer;
            short shorttype;
            char *point;
            double doubletype;
        }__attribute__((aligned(4)));  // 由于指定对齐字节小于最大自然对齐， 所以取最大自然对齐double 8字节

        /*
        [x] [ ] [ ] [ ] [x] [x] [x] [x]   ch & integer
        [x] [x] [ ] [ ] [ ] [ ] [ ] [ ]   shorttype
        [x] [x] [x] [x] [x] [x] [x] [x]   doubletype
        */
        struct Struct7{
            char ch;
            int integer;
            short shorttype;
            double doubletype;
        }__attribute__((aligned(2)));


        /*
        [x] [x] [x] [x] [x] [x] [x] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]   ch & integer & shorttype
        [x] [x] [x] [x] [x] [x] [x] [x] [x] [x] [ ] [ ] [ ] [ ] [ ] [ ]   vector
        [x] [x] [x] [x] [x] [x] [x] [x] [x] [x] [x] [x] [x] [x] [x] [x]   point & doubletype
        */
        struct Struct8{
            char ch;
            int integer;
            short shorttype;
            char vector[10];
            char *point;
            double doubletype;
        }__attribute__((aligned(16)));
    }

    
    struct ByteAlign : public iaq::AlgBase
    {
        explicit ByteAlign(iaq::Version ver = iaq::Version::V1)
            : iaq::AlgBase(ver)
        {
        }

        iaq::Version GetSupportMaxVersion() const override
        {
            return iaq::Version::V1;
        }


        size_t operator()(Situation situation) const;
    };
}


#endif // _H_BYTE_ALIGNMENT_INCLUDED__