
#include <gtest/gtest.h>
#include "Prog3.h"
#include <cmath>

using namespace Static;


TEST(NumberTest, DefaultConstructor){
    BinVec binVec;
    std::string n;

    EXPECT_EQ(binVec.output(n), "");
}


TEST(NumberTest, Constructor){
    std::string s;

    BinVec binVec(11);
    EXPECT_EQ(binVec.output(s), "01011");

    BinVec binVec_1(-0);
    EXPECT_EQ(binVec_1.output(s), "00");

    BinVec binVec_2(-21);
    EXPECT_EQ(binVec_2.output(s), "110101");

    BinVec binVec_3(43);
    EXPECT_EQ(binVec_3.output(s), "0101011");

    BinVec binVec_s_1("58");
    EXPECT_EQ(binVec_s_1.output(s), "0111010");

    BinVec binVec_s_2("0");
    EXPECT_EQ(binVec_s_2.output(s), "00");

    BinVec binVec_s_3("-27");
    EXPECT_EQ(binVec_s_3.output(s), "111011");

    BinVec binVec1(511);
    EXPECT_EQ(binVec1.output(s), "0111111111");

    BinVec binVec2(-511);
    EXPECT_EQ(binVec2.output(s), "1111111111");


    EXPECT_THROW(BinVec number5("abc"), std::invalid_argument);
}

TEST(NumberTest, DopCode){
    std::string s;

    BinVec binVec1(-12);
    EXPECT_EQ(binVec1.additionalCode().output(s), "10100");

    BinVec binVec2(-0);
    EXPECT_EQ(binVec2.additionalCode().output(s), "00");

    BinVec binVec3(59);
    EXPECT_EQ(binVec3.additionalCode().output(s), "0111011");

    BinVec binVec4("-15");
    EXPECT_EQ(binVec4.additionalCode().output(s), "10001");

    BinVec binVec5("-134");
    EXPECT_EQ(binVec5.additionalCode().output(s), "101111010");

    BinVec binVec6("48");
    EXPECT_EQ(binVec6.additionalCode().output(s), "0110000");

    BinVec binVec7("511");
    EXPECT_EQ(binVec7.additionalCode().output(s), "0111111111");
}

TEST(NumberTest, Sum){
    std::string s;

    BinVec binVec1_1(14), binVec1_2(27);
    EXPECT_EQ(smallIncludingOr(binVec1_1,binVec1_2).output(s), "0101001");

    BinVec binVec2_1("4"), binVec2_2("8");
    EXPECT_EQ(smallIncludingOr(binVec2_1, binVec2_2).output(s), "01100");

    BinVec binVec3_1("-10"), binVec3_2("-10");
    EXPECT_EQ(smallIncludingOr(binVec3_1, binVec3_2).output(s), "10100");

    BinVec binVec4_1("30"), binVec4_2("-20");
    EXPECT_EQ(smallIncludingOr(binVec4_1, binVec4_2).output(s), "010010");

    BinVec binVec5_1(-0), binVec5_2(1);
    EXPECT_EQ(smallIncludingOr(binVec5_1, binVec5_2).output(s), "01");

    BinVec binVec6_1(11), binVec6_2(-10);
    EXPECT_EQ(smallIncludingOr(binVec6_1, binVec6_2).output(s), "00101");

}


TEST(NumberTest, Sign){
    BinVec binVec(46);
    EXPECT_EQ(binVec.signum(), '0');

    BinVec binVec1(-0);
    EXPECT_EQ(binVec1.signum(), '0');

    BinVec binVec2(-12);
    EXPECT_EQ(binVec2.signum(), '1');

    BinVec binVec3(0);
    EXPECT_EQ(binVec3.signum(), '0');
}


TEST(NumberTest, Overload) {
    std::string result;

    BinVec binVec1("110");
    BinVec binVec2;
    binVec2 = binVec1;
    EXPECT_EQ("01101110", binVec2.output(result));

    BinVec binVec3(59);
    BinVec binVec4;
    binVec4 = binVec3;
    EXPECT_EQ("0111011", binVec4.output(result));

    BinVec binVec5(-78);
    BinVec binVec6;
    binVec6 = binVec5;
    EXPECT_EQ("11001110", binVec6.output(result));

    BinVec binVec7(0);
    BinVec binVec8;
    binVec8 = binVec7;
    EXPECT_EQ("00", binVec8.output(result));
}

TEST(NumberTest, Move){
    std::string result;

    BinVec binVec1(110);
    BinVec binVec2;
    binVec2 = std::move(binVec1);
    EXPECT_EQ("01101110", binVec2.output(result));
    EXPECT_EQ("", binVec1.output(result));

    BinVec binVec3(59);
    BinVec binVec4;
    binVec4 = std::move(binVec3);
    EXPECT_EQ("0111011", binVec4.output(result));
    EXPECT_EQ("", binVec3.output(result));

    BinVec binVec5(-78);
    BinVec binVec6;
    binVec6 = std::move(binVec5);
    EXPECT_EQ("11001110", binVec6.output(result));
    EXPECT_EQ("", binVec5.output(result));

    BinVec binVec7(0);
    BinVec binVec8;
    binVec8 = std::move(binVec7);
    EXPECT_EQ("00", binVec8.output(result));
    EXPECT_EQ("", binVec7.output(result));
}


TEST(NumberTest, OverloadSum) {
    std::string s;

    BinVec binVec11(14), binVec12(27);
    EXPECT_EQ((binVec11 + binVec12).output(s), "0101001");

    BinVec binVec21("4"), binVec22("8");
    EXPECT_EQ((binVec21 + binVec22).output(s), "01100");

    BinVec binVec31(-30), binVec32(1);
    EXPECT_EQ((binVec31 + binVec32).output(s), "111111");

    BinVec binVec41("-10"), binVec42("-8");
    EXPECT_EQ((binVec41 + binVec42).output(s), "10010");

    BinVec binVec51(46), binVec52(-10);
    EXPECT_EQ((binVec51 + binVec52).output(s), "0101000");

    BinVec binVec61("30"), binVec62("-24");
    EXPECT_EQ((binVec61 + binVec62).output(s), "010110");

    BinVec binVec71(14), binVec72(-30);
    EXPECT_EQ((binVec71 + binVec72).output(s), "001100");

    BinVec binVec81("6"), binVec82("-32");
    EXPECT_EQ((binVec81 + binVec82).output(s), "1100110");

    BinVec binVec91(-0), binVec92(1);
    EXPECT_EQ((binVec91 + binVec92).output(s), "01");

}


TEST(NumberTest, OverloadIsstream){
    BinVec binVec;
    std::ostringstream os;
    binVec = BinVec(112);
    os << binVec;
    EXPECT_EQ("01110000\n", os.str());


    BinVec binVec2;
    std::ostringstream os2;
    binVec2 = BinVec(-10);
    os2 << binVec2;
    EXPECT_EQ("11010\n", os2.str());

}
