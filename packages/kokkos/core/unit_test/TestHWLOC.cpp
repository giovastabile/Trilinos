/*
//@HEADER
// ************************************************************************
//
//   Kokkos: Manycore Performance-Portable Multidimensional Arrays
//              Copyright (2012) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia Corporation,
// the U.S. Government retains certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact  H. Carter Edwards (hcedwar@sandia.gov)
//
// ************************************************************************
//@HEADER
*/

#include <gtest/gtest.h>

#include <iostream>
#include <Kokkos_hwloc.hpp>

namespace Test {

class hwloc : public ::testing::Test {
protected:
  static void SetUpTestCase()
  {}

  static void TearDownTestCase()
  {}
};

TEST_F( hwloc, query)
{
  std::cout << " NUMA[" << Kokkos::hwloc::get_available_numa_count() << "]"
            << " CORE[" << Kokkos::hwloc::get_available_cores_per_numa() << "]"
            << " PU[" << Kokkos::hwloc::get_available_threads_per_core()  << "]"
            << std::endl ;
}

TEST_F( hwloc , mapping )
{
  enum { TOTAL = 30 };
  std::pair<unsigned,unsigned> thread_coord[TOTAL];
  std::pair<unsigned,unsigned> core_topo(1,15);
  std::pair<unsigned,unsigned> team_topo ;

  //----------------------------------------

  team_topo.first = 1 ;
  team_topo.second = TOTAL ;

  Kokkos::Impl::host_thread_mapping( team_topo ,
                                     core_topo ,
                                     core_topo ,
                                     thread_coord );

  std::cout << "team(" << team_topo.first
            << "," << team_topo.second
            << ") {" ;
  for ( unsigned i = 0 ; i < TOTAL ; ++i ) {
    std::cout << " " << thread_coord[i].first
              << "." << thread_coord[i].second ;
  }
  std::cout << " }" << std::endl ;

  //----------------------------------------

  team_topo.first = 5 ;
  team_topo.second = TOTAL / 5 ;

  Kokkos::Impl::host_thread_mapping( team_topo ,
                                     core_topo ,
                                     core_topo ,
                                     thread_coord );

  std::cout << "team(" << team_topo.first
            << "," << team_topo.second
            << ") {" ;
  for ( unsigned i = 0 ; i < TOTAL ; ++i ) {
    std::cout << " " << thread_coord[i].first
              << "." << thread_coord[i].second ;
  }
  std::cout << " }" << std::endl ;

}

}

