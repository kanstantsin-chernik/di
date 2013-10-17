//
// Copyright (c) 2012-2013 Krzysztof Jusiak (krzysztof at jusiak dot net)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include "boost/di/concepts.hpp"
#include <boost/mpl/int.hpp>

#include <boost/test/unit_test.hpp>

#include "data.hpp"
#include "fake_dependency_base_of.hpp"
#include "fake_scope.hpp"
#include "contains_all.hpp"

namespace boost {
namespace di {

BOOST_AUTO_TEST_CASE(bind_impl) {
    BOOST_CHECK((
        contains_all<
            scope<fake_scope<>>::bind<
                bind<i, impl>::type
            >
          , mpl::vector<
                fake_dependency_base_of<fake_scope<>, i, impl>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(bind_int_value) {
    const int i = 42;
    BOOST_CHECK((
        contains_all<
            scope<fake_scope<>>::bind<
                bind_int<i>::type
            >
          , mpl::vector<
                fake_dependency_base_of<fake_scope<>, int, mpl::int_<i>>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(bind_int_value_in_name) {
    const int i = 42;
    BOOST_CHECK((
        contains_all<
            scope<fake_scope<>>::bind<
                bind_int<i>::in_name<void>::type
            >
          , mpl::vector<
                fake_dependency_base_of<fake_scope<>, int, mpl::int_<i>, void>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(bind_int_value_in_call) {
    const int i = 42;
    BOOST_CHECK((
        contains_all<
            scope<fake_scope<>>::bind<
                bind_int<i>::in_call<c0>::type
            >
          , mpl::vector<
                fake_dependency_base_of<fake_scope<>, int, mpl::int_<i>, void, c0>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(bind_int_value_in_name_in_call) {
    const int i = 42;
    BOOST_CHECK((
        contains_all<
            scope<fake_scope<>>::bind<
                bind_int<i>::in_name<void>::in_call<c0>::type
            >
          , mpl::vector<
                fake_dependency_base_of<fake_scope<>, int, mpl::int_<i>, void, c0>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(bind_int_value_in_call_in_name) {
    const int i = 42;
    BOOST_CHECK((
        contains_all<
            scope<fake_scope<>>::bind<
                bind_int<i>::in_call<c0>::in_name<void>::type
            >
          , mpl::vector<
                fake_dependency_base_of<fake_scope<>, int, mpl::int_<i>, void, c0>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(bind_string_value) {
    using s = mpl::string<'s'>;
    BOOST_CHECK((
        contains_all<
            scope<fake_scope<>>::bind<
                bind_string<s>::type
            >
          , mpl::vector<
                fake_dependency_base_of<fake_scope<>, std::string, s>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(bind_string_value_in_name) {
    using s = mpl::string<'s'>;
    BOOST_CHECK((
        contains_all<
            scope<fake_scope<>>::bind<
                bind_string<s>::in_name<void>::type
            >
          , mpl::vector<
                fake_dependency_base_of<fake_scope<>, std::string, s, void>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(bind_string_value_in_name_in_call) {
    using s = mpl::string<'s'>;
    BOOST_CHECK((
        contains_all<
            scope<fake_scope<>>::bind<
                bind_string<s>::in_name<void>::in_call<c0, c1>::type
            >
          , mpl::vector<
                fake_dependency_base_of<fake_scope<>, std::string, s, void, c0, c1>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(bind_string_value_in_call_in_name) {
    using s = mpl::string<'s'>;
    BOOST_CHECK((
        contains_all<
            scope<fake_scope<>>::bind<
                bind_string<s>::in_call<c0, c1>::in_name<void>::type
            >
          , mpl::vector<
                fake_dependency_base_of<fake_scope<>, std::string, s, void, c0, c1>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(bind_string_value_in_call) {
    using s = mpl::string<'s'>;
    BOOST_CHECK((
        contains_all<
            scope<fake_scope<>>::bind<
                bind_string<s>::in_call<c0>::type
            >
          , mpl::vector<
                fake_dependency_base_of<fake_scope<>, std::string, s, void, c0>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(bind_vector_value) {
    BOOST_CHECK((
        contains_all<
            bind_vector<int, int_<42>>
          , mpl::vector<
                fake_dependency_base_of<scopes::deduce, std::vector<int>, make_vector<int, mpl::vector<int_<42>>>>::type
              , fake_dependency_base_of<scopes::deduce, std::vector<shared_ptr<int>>, make_vector<shared_ptr<int>, mpl::vector<shared_ptr<int_<42>>>>>::type
              , fake_dependency_base_of<scopes::deduce, std::vector<unique_ptr<int>>, make_vector<unique_ptr<int>, mpl::vector<unique_ptr<int_<42>>>>>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_deduce_empty) {
    BOOST_CHECK((
        contains_all<
            deduce<>::type
          , mpl::vector<>
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_deduce_one) {
    BOOST_CHECK((
        contains_all<
            deduce<int>::type
          , mpl::vector<
                fake_dependency_base_of<scopes::deduce, int>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_deduce_many) {
    BOOST_CHECK((
        contains_all<
            deduce<int, double, float>::type
          , mpl::vector<
                fake_dependency_base_of<scopes::deduce, int>::type
              , fake_dependency_base_of<scopes::deduce, double>::type
              , fake_dependency_base_of<scopes::deduce, float>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_per_request_empty) {
    BOOST_CHECK((
        contains_all<
            per_request<>::type
          , mpl::vector<>
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_per_request_one) {
    BOOST_CHECK((
        contains_all<
            per_request<int>::type
          , mpl::vector<
                fake_dependency_base_of<scopes::per_request<>, int>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_per_request_many) {
    BOOST_CHECK((
        contains_all<
            per_request<int, double, float>::type
          , mpl::vector<
                fake_dependency_base_of<scopes::per_request<>, int>::type
              , fake_dependency_base_of<scopes::per_request<>, double>::type
              , fake_dependency_base_of<scopes::per_request<>, float>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_scoped_empty) {
    BOOST_CHECK((
        contains_all<
            scoped<>::type
          , mpl::vector<>
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_scoped_one) {
    BOOST_CHECK((
        contains_all<
            scoped<int>::type
          , mpl::vector<
                fake_dependency_base_of<scopes::scoped<>, int>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_scoped_many) {
    BOOST_CHECK((
        contains_all<
            scoped<int, double, float>::type
          , mpl::vector<
                fake_dependency_base_of<scopes::scoped<>, int>::type
              , fake_dependency_base_of<scopes::scoped<>, double>::type
              , fake_dependency_base_of<scopes::scoped<>, float>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_session_empty) {
    BOOST_CHECK((
        contains_all<
            session<>::type
          , mpl::vector<>
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_session_one) {
    BOOST_CHECK((
        contains_all<
            session<int>::type
          , mpl::vector<
                fake_dependency_base_of<scopes::session<>, int>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_session_many) {
    BOOST_CHECK((
        contains_all<
            session<int, double, float>::type
          , mpl::vector<
                fake_dependency_base_of<scopes::session<>, int>::type
              , fake_dependency_base_of<scopes::session<>, double>::type
              , fake_dependency_base_of<scopes::session<>, float>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(scope_with_call_stack) {
    BOOST_CHECK((
        contains_all<
            scope<fake_scope<>>::bind<
                bind<i, impl>::in_call<call_stack<c0, c1>>::type
            >
          , mpl::vector<
                fake_dependency_base_of<fake_scope<>, i, impl, void, call_stack<c0, c1>>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(per_thread_empty) {
    BOOST_CHECK((
        contains_all<
            per_thread<>::type
          , mpl::vector<
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(per_thread_one) {
    BOOST_CHECK((
        contains_all<
            per_thread<int>::type
          , mpl::vector<
                fake_dependency_base_of<scopes::per_thread<scopes::deduce>, int>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(per_thread_many) {
    BOOST_CHECK((
        contains_all<
            per_thread<int, double, float>::type
          , mpl::vector<
                fake_dependency_base_of<scopes::per_thread<scopes::deduce>, int>::type
              , fake_dependency_base_of<scopes::per_thread<scopes::deduce>, double>::type
              , fake_dependency_base_of<scopes::per_thread<scopes::deduce>, float>::type
            >
        >::value
    ));
}

BOOST_AUTO_TEST_CASE(per_thread_mix) {
    BOOST_CHECK((
        contains_all<
            per_thread<
                int
              , bind<if0, c0if0>
              , per_request<double>
              , scoped<float, char>
              , per_request<bind<c1>::in_name<float> >
              , deduce<c2>::in_call<double>
            >::type
          , mpl::vector<
                fake_dependency_base_of<scopes::per_thread<scopes::deduce>, int>::type
              , fake_dependency_base_of<scopes::per_thread<scopes::deduce>, if0, c0if0>::type
              , fake_dependency_base_of<scopes::per_thread<scopes::per_request<>>, double>::type
              , fake_dependency_base_of<scopes::per_thread<scopes::scoped<>>, float>::type
              , fake_dependency_base_of<scopes::per_thread<scopes::scoped<>>, char>::type
              , fake_dependency_base_of<scopes::per_thread<scopes::per_request<>>, c1, c1, float>::type
              , fake_dependency_base_of<scopes::per_thread<scopes::deduce>, c2, c2, void, double>::type
            >
        >::value
    ));
}

} // namespace di
} // namespace boost

