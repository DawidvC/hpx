# Copyright (c) 2014 Thomas Heller
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# Try building an external cmake based project ...

macro(create_cmake_test name hpx_dir)
  set(build_dir "${CMAKE_CURRENT_BINARY_DIR}/${name}")
  add_custom_target(${name}.remove_build_dir
    COMMAND "${CMAKE_COMMAND}" -E remove_directory "${build_dir}" VERBATIM
  )
  add_custom_target(${name}.make_build_dir
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${build_dir}" VERBATIM
  )
  add_dependencies(${name}.make_build_dir ${name}.remove_build_dir)
  add_custom_target(${name}.make_configure
    COMMAND
      "${CMAKE_COMMAND}" -E chdir "${build_dir}" "${CMAKE_COMMAND}"
      "${hpx_SOURCE_DIR}/tests/unit/build/src"
      -DHPX_DIR=${hpx_dir}
      -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
      -DCMAKE_BUILD_TYPE=$<CONFIGURATION> VERBATIM)
  add_dependencies(${name}.make_configure ${name}.make_build_dir hpx iostreams_component)
  if(NOT HPX_STATIC_LINKING)
    add_dependencies(${name}.make_configure hpx_init hpx_serialization)
  endif()
  add_custom_target(${name}.make_compile
    COMMAND "${CMAKE_COMMAND}" --build "${build_dir}" VERBATIM
  )
  add_dependencies(${name}.make_compile ${name}.make_configure)
  add_hpx_pseudo_target(${name})
  add_hpx_pseudo_dependencies(${name} ${name}.make_compile)

  if(MSVC)
    set_target_properties(${name}.remove_build_dir PROPERTIES
      FOLDER "Tests/Unit/Build")
    set_target_properties(${name}.make_build_dir PROPERTIES
      FOLDER "Tests/Unit/Build")
    set_target_properties(${name}.make_configure PROPERTIES
      FOLDER "Tests/Unit/Build")
    set_target_properties(${name}.make_compile PROPERTIES
      FOLDER "Tests/Unit/Build")
  endif()
#  add_hpx_unit_test(
#    "build" ${name}
#    EXECUTABLE "${build_dir}/test"
#  )
endmacro()

macro(create_pkgconfig_test name hpx_dir)
  set(build_dir "${CMAKE_CURRENT_BINARY_DIR}/${name}")
  add_custom_target(${name}.remove_build_dir
    COMMAND "${CMAKE_COMMAND}" -E remove_directory "${build_dir}" VERBATIM
  )
  add_custom_target(${name}.make_build_dir
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${build_dir}" VERBATIM
  )
  add_dependencies(${name}.make_build_dir ${name}.remove_build_dir)
  add_custom_target(${name}.make_compile
    COMMAND
      "${CMAKE_COMMAND}" -E chdir "${build_dir}" make
      -f "${hpx_SOURCE_DIR}/tests/unit/build/src/Makefile"
      SRC_DIR=${hpx_SOURCE_DIR}/tests/unit/build/src
      HPX_DIR=${hpx_dir}
      CXX=${CMAKE_CXX_COMPILER}
      CXX_FLAGS=${CMAKE_CXX_FLAGS_SAFE}
      PKG_CONFIG=${PKG_CONFIG_EXECUTABLE}
      BUILD_TYPE=$<CONFIGURATION> VERBATIM)
  add_dependencies(${name}.make_compile ${name}.make_build_dir hpx iostreams_component)
  if(NOT HPX_STATIC_LINKING)
    add_dependencies(${name}.make_compile hpx_init hpx_serialization)
  endif()
  add_hpx_pseudo_target(${name})
  add_hpx_pseudo_dependencies(${name} ${name}.make_compile)

#  add_hpx_unit_test(
#    "build" ${name}
#    EXECUTABLE "${build_dir}/test"
#  )
endmacro()

create_cmake_test(
  cmake_build_dir_test
  "${CMAKE_BINARY_DIR}/lib/cmake/hpx")

create_cmake_test(
  cmake_install_dir_test
  "${CMAKE_INSTALL_PREFIX}/lib/cmake/hpx"
)

find_package(PkgConfig)
if(PKGCONFIG_FOUND AND NOT MSVC)
  create_pkgconfig_test(
    pkgconfig_build_dir_test
    "${CMAKE_BINARY_DIR}/lib/pkgconfig")

  create_pkgconfig_test(
    pkgconfig_install_dir_test
    "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig")
endif()

set(tests
  build_dir
  install_dir)

foreach(system cmake pkgconfig)
  add_hpx_pseudo_target(tests.unit.build.${system})
  foreach(test ${tests})
    add_hpx_pseudo_target(tests.unit.build.${system}.${test})
    add_hpx_pseudo_dependencies(tests.unit.build.${system}.${test}
      ${system}_${test}_test)
    add_hpx_pseudo_dependencies(tests.unit.build.${system}
      tests.unit.build.${system}.${test})
  endforeach()

  add_hpx_pseudo_dependencies(tests.unit.build
    tests.unit.build.${system})
endforeach()
