//  Copyright (c) 2007-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PP_IS_ITERATING

#if !defined(HPX_RUNTIME_ACTIONS_FUNCTION_OPERATORS_MAY_09_2012_0420PM)
#define HPX_RUNTIME_ACTIONS_FUNCTION_OPERATORS_MAY_09_2012_0420PM

#include <hpx/config/forceinline.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/enum_params.hpp>

    template <typename LocalResult>
    struct sync_invoke_0
    {
        template <typename IdType>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::false_, BOOST_SCOPED_ENUM(launch) policy,
            IdType const& id, error_code& ec)
        {
            return hpx::async<action>(policy, id).get(ec);
        }

        template <typename IdType>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::true_, BOOST_SCOPED_ENUM(launch) policy,
            IdType const& id, error_code& ec)
        {
            return hpx::async<action>(policy, id);
        }
    };

    template <typename IdType>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                util::tuple_size<arguments_type>::value == 0>,
            boost::is_same<IdType, naming::id_type> >,
        local_result_type
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        error_code& ec = throws) const
    {
        return util::void_guard<local_result_type>(),
            sync_invoke_0<local_result_type>::call(is_future_pred(),
                policy, id, ec);
    }

    template <typename IdType>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                util::tuple_size<arguments_type>::value == 0>,
            boost::is_same<IdType, naming::id_type> >,
        local_result_type
    >::type
    operator()(IdType const& id, error_code& ec = throws) const
    {
        return util::void_guard<local_result_type>(),
            sync_invoke_0<local_result_type>::call(is_future_pred(),
                launch::sync, id, ec);
    }

#if !defined(HPX_USE_PREPROCESSOR_LIMIT_EXPANSION)
#  include <hpx/runtime/actions/preprocessed/define_function_operators.hpp>
#else

#if defined(__WAVE__) && defined(HPX_CREATE_PREPROCESSED_FILES)
#  pragma wave option(preserve: 1, line: 0, output: "preprocessed/define_function_operators_" HPX_LIMIT_STR ".hpp")
#endif

#define BOOST_PP_ITERATION_PARAMS_1                                           \
    (3, (1, HPX_ACTION_ARGUMENT_LIMIT,                                        \
    "hpx/runtime/actions/define_function_operators.hpp"))                     \
    /**/

#include BOOST_PP_ITERATE()

#if defined(__WAVE__) && defined (HPX_CREATE_PREPROCESSED_FILES)
#  pragma wave option(output: null)
#endif

#endif // !defined(HPX_USE_PREPROCESSOR_LIMIT_EXPANSION)

#endif

///////////////////////////////////////////////////////////////////////////////
//  Preprocessor vertical repetition code
///////////////////////////////////////////////////////////////////////////////
#else // !BOOST_PP_IS_ITERATING

#define N BOOST_PP_ITERATION()

    ///////////////////////////////////////////////////////////////////////////
    template <typename LocalResult>
    struct BOOST_PP_CAT(sync_invoke_, N)
    {
        template <BOOST_PP_ENUM_PARAMS(N, typename Arg)>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::false_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, HPX_ENUM_FWD_ARGS(N, Arg, arg),
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                HPX_ENUM_FORWARD_ARGS(N, Arg, arg)).get(ec);
        }

        template <BOOST_PP_ENUM_PARAMS(N, typename Arg)>
        BOOST_FORCEINLINE static LocalResult call(
            boost::mpl::true_, BOOST_SCOPED_ENUM(launch) policy,
            naming::id_type const& id, HPX_ENUM_FWD_ARGS(N, Arg, arg),
            error_code& ec)
        {
            return hpx::async<action>(policy, id,
                HPX_ENUM_FORWARD_ARGS(N, Arg, arg));
        }
    };

    template <typename IdType, BOOST_PP_ENUM_PARAMS(N, typename Arg)>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                util::tuple_size<arguments_type>::value == N>,
            boost::is_same<IdType, naming::id_type> >,
        local_result_type
    >::type
    operator()(BOOST_SCOPED_ENUM(launch) policy, IdType const& id,
        HPX_ENUM_FWD_ARGS(N, Arg, arg), error_code& ec = throws) const
    {
        return util::void_guard<local_result_type>(),
            BOOST_PP_CAT(sync_invoke_, N)<local_result_type>::call(
                is_future_pred(), policy, id,
                HPX_ENUM_FORWARD_ARGS(N, Arg, arg), ec);
    }

    template <typename IdType, BOOST_PP_ENUM_PARAMS(N, typename Arg)>
    BOOST_FORCEINLINE typename boost::enable_if<
        boost::mpl::and_<
            boost::mpl::bool_<
                util::tuple_size<arguments_type>::value == N>,
            boost::is_same<IdType, naming::id_type> >,
        local_result_type
    >::type
    operator()(IdType const& id, HPX_ENUM_FWD_ARGS(N, Arg, arg),
        error_code& ec = throws) const
    {
        return util::void_guard<local_result_type>(),
            BOOST_PP_CAT(sync_invoke_, N)<local_result_type>::call(
                is_future_pred(), launch::sync, id,
                HPX_ENUM_FORWARD_ARGS(N, Arg, arg), ec);
    }

#undef N

#endif // !BOOST_PP_IS_ITERATING
