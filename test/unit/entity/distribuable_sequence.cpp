//==================================================================================================
/*
  MMM - Massively Modernized MPI for C++20
  Copyright : MMM Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include <mmm/mmm.hpp>
#include <span>

TTS_CASE("TODO CHECK for distribuable_sequence<T>")
{
  TTS_EQUAL(mmm::distribuable_sequence<int>().status(), false);
  TTS_EQUAL(mmm::distribuable_sequence<int>().root(), 0);

  int size = mmm::context.size();
  int mul = 4;
  //this number can be as big as we want
  int k = 100;
  //this number should be between 0 and the size
  int p = 1;

  auto dist_seq1 = mmm::distribuable_sequence<int>(0);
  auto dist_seq2 = mmm::distribuable_sequence<int>(size);
  auto dist_seq3 = mmm::distribuable_sequence<int>(size * mul);
  auto dist_seq4 = mmm::distribuable_sequence<int>(size + k);
  auto dist_seq5 = mmm::distribuable_sequence<int>(size - p);

  TTS_EQUAL(dist_seq1.status(), false);
  TTS_EQUAL(dist_seq1.root(), 0);
  TTS_EQUAL(dist_seq1.local_size(), 0);
  TTS_EQUAL(dist_seq2.local_size(), 1);
  TTS_EQUAL(dist_seq3.local_size(), mul);
  //pour la local size de dist_seq(4/5) le résultat n'est que celui pour le processus root pad énormément de sens enfaite de tester


  for(int i = 0; i < size; i++)
  {
      TTS_EQUAL(dist_seq1.count(i), 0);
      TTS_EQUAL(dist_seq1.offset(i), 0);

      TTS_EQUAL(dist_seq2.count(i), 1);
      TTS_EQUAL(dist_seq2.offset(i), i);

      TTS_EQUAL(dist_seq3.count(i), mul);
      TTS_EQUAL(dist_seq3.offset(i), mul * i);

      TTS_EQUAL(dist_seq4.count(i), 1 + (i < k%size ? (k/size) + 1 : (k/size)));
      TTS_EQUAL(dist_seq4.offset(i), i * (k + size)/size + (i * (k + size)%size != 0 ? 1 : 0));

      TTS_EQUAL(dist_seq5.count(i), ( i < size - p ? 1 : 0));
      TTS_EQUAL(dist_seq5.offset(i), ( i < size - p ? i : (size - p)));
  }
};

TTS_CASE("SCATTER TEST for distribuable_sequence<T>")
{
  int size = mmm::context.size();
  int rank = mmm::context.rank();
  int nb_elem = 10;
  int mul = 4;
  int p = 1;
  mmm::distribuable_sequence<int> dist_seq0(0);
  mmm::distribuable_sequence<int> dist_seq1(size);
  mmm::distribuable_sequence<int> dist_seq2(size * mul);
  mmm::distribuable_sequence<int> dist_seq3(size + nb_elem);
  mmm::distribuable_sequence<int> dist_seq4(size - p);

  for(int i = 0; i < size + nb_elem; i++)
  {
    dist_seq3[i] = i;
  }

  if(rank == dist_seq3.root()) 
  {
    //Use of a span to see if the vec is [0,1,2,3,...,9]
    std::span<int> mySpan(dist_seq3.data(), dist_seq3.size());
    TTS_EQUAL(mySpan.size(), size + nb_elem);
    for(std::size_t i = 0; i < mySpan.size(); i++)
    {
      TTS_EQUAL(mySpan[i], i);
    }
  }

  dist_seq3.scatter();

  //Iterate on each proc of our system to see if they have [0,1,2], [3,4,5], [6,7], [8,9]
  for(int i = 0; i < size; i++)
  {
    //We have to creat a span to see if the distributed_seq have the right value
    //Check if the size of our vector correspond to the count
    if(i == rank)
    {
    }
  }

  dist_seq3.gather();

  if(rank == dist_seq3.root()) 
  {
    //See if we came back to the initial distributed vector
    std::span<int> mySpan(dist_seq3.begin(), dist_seq3.size());
    TTS_EQUAL(mySpan.size(), size + nb_elem);
    for(std::size_t i = 0; i < mySpan.size(); i++)
    {
      TTS_EQUAL(mySpan[i], i);
    }
  }
};
