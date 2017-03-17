#include <boost/test/unit_test.hpp>
#include <temperature/Dummy.hpp>

using namespace temperature;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    temperature::DummyClass dummy;
    dummy.welcome();
}
