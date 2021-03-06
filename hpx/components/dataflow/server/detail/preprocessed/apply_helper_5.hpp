// Copyright (c) 2007-2013 Hartmut Kaiser
// Copyright (c) 2012-2013 Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file has been automatically generated using the Boost.Wave tool.
// Do not edit manually.


    template <typename Action>
    struct apply_helper<1, Action>
    {
        template <typename Vector>
        void operator()(
            naming::id_type const & cont
          , naming::id_type const & id
          , Vector & args
        ) const
        {
            LLCO_(info)
                << "dataflow apply action "
                << hpx::actions::detail::get_action_name<Action>();
            hpx::apply_c<Action>(
                cont
              , id
              , std::move(boost::fusion::at_c< 0>(args))
            );
        }
    };
     
    template <typename Action>
    struct apply_helper<2, Action>
    {
        template <typename Vector>
        void operator()(
            naming::id_type const & cont
          , naming::id_type const & id
          , Vector & args
        ) const
        {
            LLCO_(info)
                << "dataflow apply action "
                << hpx::actions::detail::get_action_name<Action>();
            hpx::apply_c<Action>(
                cont
              , id
              , std::move(boost::fusion::at_c< 0>(args)) , std::move(boost::fusion::at_c< 1>(args))
            );
        }
    };
     
    template <typename Action>
    struct apply_helper<3, Action>
    {
        template <typename Vector>
        void operator()(
            naming::id_type const & cont
          , naming::id_type const & id
          , Vector & args
        ) const
        {
            LLCO_(info)
                << "dataflow apply action "
                << hpx::actions::detail::get_action_name<Action>();
            hpx::apply_c<Action>(
                cont
              , id
              , std::move(boost::fusion::at_c< 0>(args)) , std::move(boost::fusion::at_c< 1>(args)) , std::move(boost::fusion::at_c< 2>(args))
            );
        }
    };
     
    template <typename Action>
    struct apply_helper<4, Action>
    {
        template <typename Vector>
        void operator()(
            naming::id_type const & cont
          , naming::id_type const & id
          , Vector & args
        ) const
        {
            LLCO_(info)
                << "dataflow apply action "
                << hpx::actions::detail::get_action_name<Action>();
            hpx::apply_c<Action>(
                cont
              , id
              , std::move(boost::fusion::at_c< 0>(args)) , std::move(boost::fusion::at_c< 1>(args)) , std::move(boost::fusion::at_c< 2>(args)) , std::move(boost::fusion::at_c< 3>(args))
            );
        }
    };
     
    template <typename Action>
    struct apply_helper<5, Action>
    {
        template <typename Vector>
        void operator()(
            naming::id_type const & cont
          , naming::id_type const & id
          , Vector & args
        ) const
        {
            LLCO_(info)
                << "dataflow apply action "
                << hpx::actions::detail::get_action_name<Action>();
            hpx::apply_c<Action>(
                cont
              , id
              , std::move(boost::fusion::at_c< 0>(args)) , std::move(boost::fusion::at_c< 1>(args)) , std::move(boost::fusion::at_c< 2>(args)) , std::move(boost::fusion::at_c< 3>(args)) , std::move(boost::fusion::at_c< 4>(args))
            );
        }
    };
     
