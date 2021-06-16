#include <qtudt.h>

const int N::UDT::SequenceNo::SeqNoTH  = 0x3FFFFFFF ;
const int N::UDT::SequenceNo::MaxSeqNo = 0x7FFFFFFF ;

N::UDT::SequenceNo:: SequenceNo (void)
{
}

N::UDT::SequenceNo::~SequenceNo (void)
{
}

int N::UDT::SequenceNo::seqcmp(int seq1,int seq2)
{
  return ( abs(seq1 - seq2) < SeqNoTH ) ?
         ( seq1 - seq2                ) :
         ( seq2 - seq1                ) ;
}

int N::UDT::SequenceNo::seqlen(int seq1,int seq2)
{
  return ( seq1 <= seq2                ) ?
         ( seq2  - seq1 + 1            ) :
         ( seq2  - seq1 + MaxSeqNo + 2 ) ;
}

int N::UDT::SequenceNo::seqoff(int seq1,int seq2)
{
  int ds = seq1 - seq2                                     ;
  if ( abs(ds) < SeqNoTH ) return   ( -ds                ) ;
  if ( ds      < 0       ) return - (  ds + MaxSeqNo + 1 ) ;
  return                            ( -ds + MaxSeqNo + 1 ) ;
}

int N::UDT::SequenceNo::incseq(int seq)
{
  return ( seq == MaxSeqNo ) ? 0 : ( seq + 1 ) ;
}

int N::UDT::SequenceNo::decseq(int seq)
{
  return ( seq == 0 ) ? MaxSeqNo : ( seq - 1 ) ;
}

int N::UDT::SequenceNo::incseq(int seq,int inc)
{
  return ( ( MaxSeqNo - seq ) >= inc ) ?
         ( seq + inc                 ) :
         ( seq - MaxSeqNo + inc - 1  ) ;
}
