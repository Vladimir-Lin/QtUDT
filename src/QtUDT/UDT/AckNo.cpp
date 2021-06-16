#include <qtudt.h>

const int N::UDT::AckNo::MaxAckSeqNo = 0x7FFFFFFF ;

N::UDT::AckNo:: AckNo (void)
{
}

N::UDT::AckNo::~AckNo (void)
{
}

int N::UDT::AckNo::incack(int ackno)
{
  return ( ackno == MaxAckSeqNo ) ? 0 : ( ackno + 1 ) ;
}
