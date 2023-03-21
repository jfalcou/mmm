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

  TTS_EQUAL(dist_seq1.root(), 0);
  TTS_EQUAL(dist_seq1.size(), 0);
  TTS_EQUAL(dist_seq2.size(), 1);
  TTS_EQUAL(dist_seq3.size(), mul);
  //pour la local size de dist_seq(4/5) le résultat n'est que celui pour le processus root pad énormément de sens enfaite de tester


  for(int i = 0; i < size; i++)
  {
      TTS_EQUAL(dist_seq1.counts(), 0);
      TTS_EQUAL(dist_seq1.offsets(), 0);

      TTS_EQUAL(dist_seq2.counts(), 1);
      TTS_EQUAL(dist_seq2.offsets(), i);

      TTS_EQUAL(dist_seq3.counts(), mul);
      TTS_EQUAL(dist_seq3.offsets(), mul * i);

      TTS_EQUAL(dist_seq4.counts(), 1 + (i < k%size ? (k/size) + 1 : (k/size)));
      TTS_EQUAL(dist_seq4.offsets(), i * (k + size)/size + (i * (k + size)%size != 0 ? 1 : 0));

      TTS_EQUAL(dist_seq5.counts(), ( i < size - p ? 1 : 0));
      TTS_EQUAL(dist_seq5.offsets(), ( i < size - p ? i : (size - p)));
  }
};

TTS_CASE("SCATTER TEST for distribuable_sequence<T>")
{
  //int size = mmm::context.size();
  //mmm::pid rank = mmm::context.rank();
//
  //int nb_elem = 12;
  //int mul = 4;
  //int p = 1;

  //mmm::distribuable_sequence<int> dist_seq(nb_elem, 0);

  //int myArray[nb_elem];
  //for (int i = 0; i < nb_elem; i++)
  //{
  //  myArray[i] = i;
  //}
  //
  //for(int i = 0; i < nb_elem; i++)
  // {
  //   if(rank == dist_seq.root())
  //   {
  //     dist_seq[i] = i;
  //   }
  // }

  //auto s = mmm::scatter(dist_seq);
//
  //std::span mySpan{s};
  //TTS_EQUAL(mySpan.size(), 3);
//
  //for(int i = 0; i < size; i++)
  //{
  //  TTS_EQUAL(mySpan, std::span{[i*3, i*3+1, i*3+2]})
  //}

  //mmm::distribuable_sequence<int> dist_seq(nb_elem, 0);
  //auto count = dist_seq.counts();
  //auto offset = dist_seq.offsets();
  //auto s = mmm::scatter(dist_seq);
  //int offset_cpt = 0;
//
  //for(int i = 0; i < size; i++)
  //{
  //  int count_cpt = 0;
  //  for(e : s)
  //  {
  //    count_cpt++;
  //  }
  //  TTS_EQUAL(count[i], cpt);
  //  TTS_EQUAL(offset[i], offset_cpt);
//
  //  offset_cpt += count_cpt;
  //}
};
