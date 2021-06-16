#include <qtudt.h>

const int N::UDT::MessageNo::MsgNoTH  = 0xFFFFFFF  ; // threshold for comparing msg. no.
const int N::UDT::MessageNo::MaxMsgNo = 0x1FFFFFFF ; // maximum message number used in UDT

N::UDT::MessageNo:: MessageNo (void)
{
}

N::UDT::MessageNo::~MessageNo (void)
{
}

int N::UDT::MessageNo::msgcmp(int msgno1,int msgno2)
{
  int ds = msgno1 - msgno2                ;
  return ( abs(ds) < MsgNoTH ) ? ds : -ds ;
}

int N::UDT::MessageNo::msglen(int msgno1,int msgno2)
{
  return ( msgno1 <= msgno2                ) ?
         ( msgno2  - msgno1 + 1            ) :
         ( msgno2  - msgno1 + MaxMsgNo + 2 ) ;
}

int N::UDT::MessageNo::msgoff(int msgno1,int msgno2)
{
  int ds = ( msgno1 - msgno2 )                            ;
  if ( abs(ds) < MsgNoTH) return   ( -ds                ) ;
  if ( ds      < 0      ) return - (  ds + MaxMsgNo + 1 ) ;
  return                           ( -ds + MaxMsgNo + 1 ) ;
}

int N::UDT::MessageNo::incmsg(int msgno)
{
  return ( msgno == MaxMsgNo ) ? 0 : ( msgno + 1 ) ;
}
