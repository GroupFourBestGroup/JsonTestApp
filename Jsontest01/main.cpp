#include <iostream>
#include <conio.h>
#include "rapidjson/error/en.h"
#include "rapidjson/error/error.h"
#include "rapidjson/reader.h"
#include "rapidjson/stream.h"

using namespace rapidjson;

class Handler : public BaseReaderHandler<UTF8<> > {
public:
	bool Double(double d) {
		std::cout << d;
		return true;
	}
};

void test(const char* json) {
	std::cout << json << " -> ";
	Reader reader;
	StringStream stream(json);
	Handler handler;
	if (!reader.Parse(stream, handler)) {
		std::cout << GetParseError_En(reader.GetParseErrorCode());
	}
	std::cout << std::endl;
}

int main() {

	long double max = std::numeric_limits<long double>::max();
	double max2 = DBL_MAX;
	double inf = std::numeric_limits<double>::infinity();

	if (inf > max) {
		std::cout << inf << " is greater than " << max << '\n';
	}

	// Pie, yummmm
	test("3.14");

	// Positives with decimal
	test("1.7e307");
	test("1.8e307");
	test("1.7e308");
	test("1.8e308");
	test("1.0e310");
	test("1.00e310");

	// positives without decimal
	test("1e308");
	test("5e308");
	test("1e309");

	// Negatives with decimal
	test("-1.7e308");
	test("-1.8e308");

	// Negatives without decimal
	test("-1e309");

	getch();
}
