//  Copyright (c) 2007-2012 Hartmut Kaiser
//  Copyright (c)      2011 Bryce Lelbach
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_COMPONENTS_CONSOLE_DEC_16_2008_0427PM)
#define HPX_COMPONENTS_CONSOLE_DEC_16_2008_0427PM

#include <string>
#include <vector>

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/components/component_type.hpp>
#include <hpx/runtime/actions/plain_action.hpp>
#include <hpx/util/logging.hpp>
#include <hpx/util/void_cast.hpp>

#include <boost/fusion/include/vector.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace components
{
    typedef boost::fusion::vector3<
        logging_destination, std::size_t, std::string
    > message_type;

    typedef std::vector<message_type> messages_type;
}}

///////////////////////////////////////////////////////////////////////////////
// non-intrusive serialization
namespace boost { namespace serialization
{
    template <typename Archive>
    void serialize(Archive&, hpx::components::message_type&, unsigned int const);
}}

//////////////////////////////////////////////////////////////////////////////
namespace hpx { namespace components { namespace server
{
    ///////////////////////////////////////////////////////////////////////////
    // console logging happens here
    void console_logging(messages_type const&);

    ///////////////////////////////////////////////////////////////////////////
    // this type is a dummy template to avoid premature instantiation of the
    // serialization support instances
    template <typename Dummy = void>
    class console_logging_action
      : public
            HPX_MAKE_ACTION_DERIVED(
                console_logging, console_logging_action<Dummy>
            )::type
    {
    private:
        typedef typename
            HPX_MAKE_ACTION_DERIVED(
                console_logging, console_logging_action
            )::type
        base_type;

    public:
        console_logging_action() {}

        // construct an action from its arguments
        console_logging_action(messages_type const& msgs)
          : base_type(msgs)
        {}

        console_logging_action(threads::thread_priority,
                messages_type const& msgs)
          : base_type(msgs)
        {}

        /// serialization support
        static void register_base()
        {
            util::void_cast_register_nonvirt<console_logging_action, base_type>();
            base_type::register_base();
        }

    public:
        template <typename Arguments>
        static util::unused_type
        execute_function(naming::address::address_type lva,
            BOOST_FWD_REF(Arguments) args)
        {
            try {
                // call the function, ignoring the return value
                console_logging(
                    boost::move(boost::fusion::at_c<0>(args)));
            }
            catch (hpx::exception const& /*e*/) {
                /**/;      // no logging!
            }
            return util::unused;
        }

    private:
        // serialization support
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive& ar, const unsigned int /*version*/)
        {
            ar & boost::serialization::base_object<base_type>(*this);
        }
    };
}}}

namespace hpx { namespace actions { namespace detail {
    template <typename Dummy>
    struct action_traits<hpx::components::server::console_logging_action<Dummy> >
    {
        typedef
            hpx::components::server::console_logging_action<Dummy>
            derived_type;
        typedef
            components::server::plain_function<derived_type>
            component_type;
            typedef hpx::util::unused_type result_type;
            typedef
                hpx::util::tuple1<hpx::components::messages_type>
                arguments_type;
            typedef action<derived_type> base_type;
    };
}}}

HPX_ACTION_DIRECT_EXECUTION(
    hpx::components::server::console_logging_action<>
)
HPX_REGISTER_PLAIN_ACTION_DECLARATION(
    hpx::components::server::console_logging_action<>
)

namespace hpx { namespace traits
{
    template <typename Dummy>
    struct needs_guid_initialization<
            hpx::actions::transfer_action<
                hpx::components::server::console_logging_action<Dummy> > >
      : boost::mpl::false_
    {};
}}

#endif

