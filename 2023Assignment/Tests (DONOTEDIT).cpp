#include "Mountains.h"
#include <thread>
#include <map>
#include "Calculations.h"

#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
namespace bdata = boost::unit_test::data;


std::vector<std::string> files = { "Alps.txt", "Carpathians.txt", "Icelandic Highlands.txt", "Pyrenees.txt" };
std::map<std::string, std::vector<std::string> > data = { {"Alps", { "Dom","Olan","Scopi","Piz Bernina","Grivola","Marmolada"}},
															{"Pyrenees",{"Aneto", "Taga", "Monte Perdido", "Pedraforca","Cerbillona", "Espadas Peak"}},
															{"Icelandic Highlands",{"Hekla","Maelifell", "Brennisteinsalda", "Modi", "Magni", "Eyjafjallajokull"}},
															{"Carpathians", {"Rysy","Gerlach","Swinica","Krivan","Mnich"}} };

struct f {
	Mountains m;
	Calculations c;
	f() : m(files) {}
	~f() {}
};

BOOST_FIXTURE_TEST_SUITE(allTests, f)

BOOST_AUTO_TEST_CASE(seeding)
{
	srand(0);
	std::string a = m.getRandomMountain();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	srand(0);
	std::string b = m.getRandomMountain();
	BOOST_TEST(a == b, "RANDOMNESS CRITERION NOT MET: You should only seed the random number generator once at the beginning of your program");
}

BOOST_AUTO_TEST_CASE(randomness)
{
	srand(0);
	std::string first = m.getRandomMountain();
	int differences = 0;
	for (int i = 0; i < 100; i++)
		if (m.getRandomMountain() != first)
			differences++;
	BOOST_TEST(differences > 70, "RANDOMNESS CRITERION NOT MET: Your random mountains don't appear to be very random");
}

BOOST_AUTO_TEST_CASE(invalidMountain)
{
	BOOST_TEST(!m.checkRange("Dummy", "Alps"), "INVALID STRING INCORRECTLY HANDLED: 'Dummy' is not a mountain.");
}

BOOST_AUTO_TEST_CASE(invalidRange)
{
	BOOST_TEST(!m.checkRange("Rysy", "Dummy"), "INVALID STRING INCORRECTLY HANDLED: 'Dummy' is not a mountain range.");
}

BOOST_DATA_TEST_CASE(allAlps, bdata::make(data["Alps"]), sample)
{
	BOOST_TEST(m.checkRange(sample, "Alps"), "FALSE NEGATIVE: " + sample + " should be in the Alps");
}

BOOST_DATA_TEST_CASE(allCarpathians, bdata::make(data["Carpathians"]), sample)
{
	BOOST_TEST(m.checkRange(sample, "Carpathians"), "FALSE NEGATIVE: " + sample + " should be in the Carpathians");
}

BOOST_DATA_TEST_CASE(allIcelandicHighlands, bdata::make(data["Icelandic Highlands"]), sample)
{
	BOOST_TEST(m.checkRange(sample, "Icelandic Highlands"), "FALSE NEGATIVE: " + sample + " should be in the Icelandic Highlands");
}

BOOST_DATA_TEST_CASE(RandomPyrenees, bdata::make(data["Pyrenees"]), sample)
{
	BOOST_TEST(m.checkRange(sample, "Pyrenees"), "FALSE NEGATIVE: " + sample + " should be in the Pyrenees");
}

BOOST_DATA_TEST_CASE(RandomWrongAnswers, bdata::random(0, 11999) ^ bdata::xrange(50), sample, idx)
{
	std::vector<std::string> names = { "Alps","Carpathians","Icelandic Highlands","Pyrenees" };
	std::string mRange = names[sample / 3000];
	int wPicker = (sample % 3000) / 1000;
	if (wPicker >= (sample / 3000))
		wPicker++;
	std::string wRange = names[wPicker];
	BOOST_TEST(!m.checkRange(data[mRange][sample % data[mRange].size()], wRange), "FALSE POSITIVE: " + data[mRange][sample % data[mRange].size()] + " is not in the " + wRange);
}

BOOST_AUTO_TEST_CASE(noHardcodedStrings)
{
	std::string line, txt;
	
	std::ifstream ifs("Mountains.cpp");
	while (std::getline(ifs, line))
		txt.append(line);
	ifs.close();
	
	ifs.open("Mountains.h");
	while (std::getline(ifs, line))
		txt.append(line);
	ifs.close();

	for(auto i : data)
		for(std::string j : i.second)
			BOOST_TEST(txt.find(j) == std::string::npos, "HARDCODED STRING PRESENT: " + j);
}

//NEW UNIT TESTS START HERE

//checkInteger
BOOST_AUTO_TEST_CASE(checkInteger)
{
	BOOST_TEST(c.checkInteger("512312") == true);
	BOOST_TEST(c.checkInteger("5tf46p") == false);
	BOOST_TEST(c.checkInteger("aksjaf") == false);
}
//editString
BOOST_AUTO_TEST_CASE(editString)
{
	BOOST_TEST(c.editString("hello world", " world") == "hello");
	BOOST_TEST(c.editString("The cat sat on the mat", " sat") == "The cat on the mat");
	BOOST_TEST(c.editString("one long boat floats on the ocean", "o") == "ne long boat floats on the ocean");
}
//vectorTrim
BOOST_AUTO_TEST_CASE(vectorTrim)
{
	std::vector<std::string> vectoriousII = { "apple.fruit", "orange.fruit", "green.fruit", "eggplant.veggie"};
	std::vector<std::string> vectoriousIII = c.vectorTrim(vectoriousII);
	BOOST_CHECK_EQUAL(vectoriousIII[0], "apple");
	BOOST_CHECK_EQUAL(vectoriousIII[1], "orange");
	BOOST_CHECK_EQUAL(vectoriousIII[2], "green");
	BOOST_CHECK_EQUAL(vectoriousIII[3], "eggplant.veggie");
}
//userInputStr
BOOST_AUTO_TEST_CASE(userInputStr)
{
	//BOOST_TEST(c.userInputStr("apple") == "apple");
}

BOOST_AUTO_TEST_CASE(percentage)
{
	//TESTS FOR 5%
	float percentageA = c.percentage(5, 100);
	//float percentageB = c.percentage(20, 1);
	BOOST_CHECK_EQUAL(percentageA, 5);
	//TESTS FOR 100%
	percentageA = c.percentage(2, 2);
	//percentageB = c.percentage(90, 6);
	BOOST_CHECK_EQUAL(percentageA, 100);
	//TESTS FOR 80%
	percentageA = c.percentage(40, 50);
	BOOST_CHECK_EQUAL(percentageA, 80);
}

BOOST_AUTO_TEST_SUITE_END()