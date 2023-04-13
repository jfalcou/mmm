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

// TTS_CASE("TODO CHECK for distribuable_sequence<T>")
// {
//   TTS_EQUAL(mmm::distribuable_sequence<int>().root(), 0);

//   int size = mmm::context.size();
//   int mul = 4;
//   //this number can be as big as we want
//   int k = 100;
//   //this number should be between 0 and the size
//   int p = 1;

//   auto dist_seq1 = mmm::distribuable_sequence<int>(0);
//   auto dist_seq2 = mmm::distribuable_sequence<int>(size);
//   auto dist_seq3 = mmm::distribuable_sequence<int>(size * mul);
//   auto dist_seq4 = mmm::distribuable_sequence<int>(size + k);
//   auto dist_seq5 = mmm::distribuable_sequence<int>(size - p);

//   TTS_EQUAL(dist_seq1.root(), 0);
//   TTS_EQUAL(dist_seq1.size(), 0);
//   TTS_EQUAL(dist_seq2.size(), 1);
//   TTS_EQUAL(dist_seq3.size(), mul);
//   //pour la local size de dist_seq(4/5) le résultat n'est que celui pour le processus root pad énormément de sens enfaite de tester


//   for(int i = 0; i < size; i++)
//   {
//       TTS_EQUAL(dist_seq1.counts(), 0);
//       TTS_EQUAL(dist_seq1.offsets(), 0);

//       TTS_EQUAL(dist_seq2.counts(), 1);
//       TTS_EQUAL(dist_seq2.offsets(), i);

//       TTS_EQUAL(dist_seq3.counts(), mul);
//       TTS_EQUAL(dist_seq3.offsets(), mul * i);

//       TTS_EQUAL(dist_seq4.counts(), 1 + (i < k%size ? (k/size) + 1 : (k/size)));
//       TTS_EQUAL(dist_seq4.offsets(), i * (k + size)/size + (i * (k + size)%size != 0 ? 1 : 0));

//       TTS_EQUAL(dist_seq5.counts(), ( i < size - p ? 1 : 0));
//       TTS_EQUAL(dist_seq5.offsets(), ( i < size - p ? i : (size - p)));
//   }
// };

TTS_CASE("SCATTER TEST for distribuable_sequence<T>")
{
  int size = mmm::context.size();
  mmm::pid rank = mmm::context.rank();
  int r = static_cast<int>(rank);

  // one element per proc
  const int sizeArray0 = 4;
  // for elemn per proc to test
  const int sizeArray1 = 16;
  // number of proc minus 1
  const int sizeArray2 = 3;

  int myArray0[sizeArray0];
  int myArray1[sizeArray1];
  int myArray2[sizeArray2];

  for (int i = 0; i < sizeArray0; i++)
  {
    myArray0[i] = i;
  }

  for (int i = 0; i < sizeArray1; i++)
  {
    myArray1[i] = i;
  }
  //for (int i = 0; i < sizeArray2; i++)
  //{
  //  myArray2[i] = i;
  //}

  mmm::distribuable_sequence<int> dist_seq(std::begin(myArray0), std::end(myArray0));

  TTS_EQUAL(dist_seq.counts()[r], dist_seq.local_size(rank));

  auto vec = mmm::scatter(dist_seq);
  std::span mySpan{vec};

  TTS_EQUAL(mySpan.size(), 1ULL);

  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < dist_seq.counts()[i]; j++)
    {
      TTS_EQUAL(mySpan[j], dist_seq.offsets()[r] + j);
    }
  }
  
  mmm::distribuable_sequence<int> dist_seq1(std::begin(myArray1), std::end(myArray1));

  TTS_EQUAL(dist_seq1.counts()[r], dist_seq1.local_size(rank));

  auto vec1 = mmm::scatter(dist_seq1);
  std::span mySpan1{vec1};

  TTS_EQUAL(mySpan1.size(), 4ULL);

  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < dist_seq1.counts()[r]; j++)
    {
      TTS_EQUAL(mySpan1[j], dist_seq1.offsets()[r] + j);
    }
  }

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

  // for(int i = 0; i < size; i++)
  // {
  //  int count_cpt = 0;
  //  for(e : s)
  //  {
  //    count_cpt++;
  //  }
  //  TTS_EQUAL(count[i], cpt);
  //  TTS_EQUAL(offset[i], offset_cpt);

  //  offset_cpt += count_cpt;
  // }
};
