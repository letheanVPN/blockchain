#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <cerrno> // For EPERM

#include <boost/version.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <boost/timer/timer.hpp>
#include <boost/chrono.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/regex.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/atomic.hpp>
#include <boost/program_options.hpp>

#if defined(TEST_LOCALE)
#include <boost/locale.hpp>
#endif

#if defined(TEST_LOG)
#include <boost/log/trivial.hpp>
#endif

// A simple class for serialization test
class MyData {
public:
    std::string name;
    int value;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & name;
        ar & value;
    }
};

// A no-op function for the thread test to execute.
void dummy_thread_func() {}

int main() {
    std::cout << "Found Boost version: " << BOOST_LIB_VERSION << std::endl;

    // Test boost::system by calling a function that is guaranteed to be in the compiled library.
    // We use a non-zero error code to prevent the compiler from optimizing away the call.
    try {
        boost::system::error_code ec(EPERM, boost::system::system_category());
        std::string msg = ec.message();
        if (msg.empty() || msg == "Success") {
            std::cerr << "boost::system test failed to get a real error message." << std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "boost::system test threw an exception: " << e.what() << std::endl;
        return 1;
    }
    std::cout << "Successfully used boost::system." << std::endl;

    // Test filesystem
    boost::filesystem::path p(".");
    if (!boost::filesystem::exists(p)) { std::cerr << "boost::filesystem failed." << std::endl; return 1; }
    std::cout << "Successfully used boost::filesystem." << std::endl;

    // Test thread by creating a thread, running it, and joining it.
    try {
        boost::thread t(dummy_thread_func);
        t.join();
    } catch (const std::exception& e) {
        std::cerr << "boost::thread test threw an exception: " << e.what() << std::endl;
        return 1;
    }
    std::cout << "Successfully used boost::thread." << std::endl;

    // Test timer and chrono
    boost::timer::cpu_timer timer;
    boost::chrono::system_clock::now();
    std::cout << "Successfully used boost::timer and boost::chrono." << std::endl;

    // Test date_time
    boost::gregorian::date d(2024, 1, 1);
    if (d.year() != 2024) { std::cerr << "boost::date_time failed." << std::endl; return 1; }
    std::cout << "Successfully used boost::date_time." << std::endl;

    // Test regex
    boost::regex expr("(\\w+), (\\w+)");
    if (!boost::regex_match("Doe, John", expr)) { std::cerr << "boost::regex failed." << std::endl; return 1; }
    std::cout << "Successfully used boost::regex." << std::endl;

    // Test serialization
    std::stringstream ss;
    MyData d_out = {"test", 123};
    boost::archive::text_oarchive oa(ss);
    oa << d_out;
    MyData d_in;
    boost::archive::text_iarchive ia(ss);
    ia >> d_in;
    if (d_in.name != "test" || d_in.value != 123) { std::cerr << "boost::serialization failed." << std::endl; return 1; }
    std::cout << "Successfully used boost::serialization." << std::endl;

    // Test atomic
    boost::atomic<int> a(5);
    a++;
    if (a.load() != 6) { std::cerr << "boost::atomic failed." << std::endl; return 1; }
    std::cout << "Successfully used boost::atomic." << std::endl;

    // Test program_options by actually parsing arguments.
    try {
        boost::program_options::options_description desc("Allowed options");
        desc.add_options()("help", "produce help message");
        const char* argv[] = {"test", "--help"};
        int argc = 2;
        boost::program_options::variables_map vm;
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
        boost::program_options::notify(vm);
        if (!vm.count("help")) { std::cerr << "boost::program_options failed." << std::endl; return 1; }
    } catch (const std::exception& e) {
        std::cerr << "boost::program_options test threw an exception: " << e.what() << std::endl;
        return 1;
    }
    std::cout << "Successfully used boost::program_options." << std::endl;

#if defined(TEST_LOCALE)
    try {
        boost::locale::generator gen;
        std::locale loc = gen("en_US.UTF-8");
        std::cout.imbue(loc);
    } catch (const std::exception& e) {
        std::cerr << "Error initializing boost::locale: " << e.what() << std::endl;
        std::cerr << "This may be due to a missing or misconfigured ICU dependency." << std::endl;
        return 1;
    }
    std::cout << "Successfully used boost::locale." << std::endl;
#endif

#if defined(TEST_LOG)
    BOOST_LOG_TRIVIAL(info) << "A trivial log message from boost::log.";
    std::cout << "Successfully used boost::log." << std::endl;
#endif

    std::cout << "Boost verification test passed." << std::endl;
    return 0;
}