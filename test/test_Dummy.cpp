#include <boost/test/unit_test.hpp>
#include <flasher/Dummy.hpp>

using namespace flasher;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    flasher::DummyClass dummy;
    dummy.welcome();
}
