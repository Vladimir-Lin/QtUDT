#include <qtudt.h>

const int N::UDT::Exception::SUCCESS      =     0 ;
const int N::UDT::Exception::ECONNSETUP   =  1000 ;
const int N::UDT::Exception::ENOSERVER    =  1001 ;
const int N::UDT::Exception::ECONNREJ     =  1002 ;
const int N::UDT::Exception::ESOCKFAIL    =  1003 ;
const int N::UDT::Exception::ESECFAIL     =  1004 ;
const int N::UDT::Exception::ECONNFAIL    =  2000 ;
const int N::UDT::Exception::ECONNLOST    =  2001 ;
const int N::UDT::Exception::ENOCONN      =  2002 ;
const int N::UDT::Exception::ERESOURCE    =  3000 ;
const int N::UDT::Exception::ETHREAD      =  3001 ;
const int N::UDT::Exception::ENOBUF       =  3002 ;
const int N::UDT::Exception::EFILE        =  4000 ;
const int N::UDT::Exception::EINVRDOFF    =  4001 ;
const int N::UDT::Exception::ERDPERM      =  4002 ;
const int N::UDT::Exception::EINVWROFF    =  4003 ;
const int N::UDT::Exception::EWRPERM      =  4004 ;
const int N::UDT::Exception::EINVOP       =  5000 ;
const int N::UDT::Exception::EBOUNDSOCK   =  5001 ;
const int N::UDT::Exception::ECONNSOCK    =  5002 ;
const int N::UDT::Exception::EINVPARAM    =  5003 ;
const int N::UDT::Exception::EINVSOCK     =  5004 ;
const int N::UDT::Exception::EUNBOUNDSOCK =  5005 ;
const int N::UDT::Exception::ENOLISTEN    =  5006 ;
const int N::UDT::Exception::ERDVNOSERV   =  5007 ;
const int N::UDT::Exception::ERDVUNBOUND  =  5008 ;
const int N::UDT::Exception::ESTREAMILL   =  5009 ;
const int N::UDT::Exception::EDGRAMILL    =  5010 ;
const int N::UDT::Exception::EDUPLISTEN   =  5011 ;
const int N::UDT::Exception::ELARGEMSG    =  5012 ;
const int N::UDT::Exception::EINVPOLLID   =  5013 ;
const int N::UDT::Exception::EASYNCFAIL   =  6000 ;
const int N::UDT::Exception::EASYNCSND    =  6001 ;
const int N::UDT::Exception::EASYNCRCV    =  6002 ;
const int N::UDT::Exception::ETIMEOUT     =  6003 ;
const int N::UDT::Exception::EPEERERR     =  7000 ;
const int N::UDT::Exception::EUNKNOWN     = -1    ;

/////////////////////////////////////////////////////////////////////////

N::UDT::Exception:: Exception (int major, int minor, int err)
                  : Major     (    major                    )
                  , Minor     (               minor         )
{
  if (-1 == err)             {
    #ifndef WIN32
    Errno = errno            ;
    #else
    Errno = GetLastError ( ) ;
    #endif
  } else Errno = err         ;
}

N::UDT::Exception:: Exception (const Exception & e)
                  : Major     (e.Major            )
                  , Minor     (e.Minor            )
                  , Errno     (e.Errno            )
                  , strMsg    (e.strMsg           )
{
}

N::UDT::Exception::~Exception()
{
}

const char * N::UDT::Exception::getErrorMessage()
{ // translate "Major:Minor" code into text message.
  switch ( Major )                                                       {
    case 0                                                               :
      strMsg = QObject::tr("Success")                                    ;
    break                                                                ;
    case 1                                                               :
      strMsg  = QObject::tr("Connection setup failure")                  ;
      strMsg += ": "                                                     ;
      switch ( Minor )                                                   {
        case 1                                                           :
          strMsg += QObject::tr("connection time out")                   ;
        break                                                            ;
        case 2                                                           :
          strMsg += QObject::tr("connection rejected")                   ;
        break                                                            ;
        case 3                                                           :
          strMsg += QObject::tr("unable to create/configure UDP socket") ;
        break                                                            ;
        case 4                                                           :
          strMsg += QObject::tr("abort for security reasons"           ) ;
        break                                                            ;
        default                                                          :
        break                                                            ;
      }                                                                  ;
    break                                                                ;
    case 2                                                               :
      switch ( Minor )                                                   {
        case 1                                                           :
          strMsg = QObject::tr("Connection was broken")                  ;
        break                                                            ;
        case 2                                                           :
          strMsg = QObject::tr("Connection does not exist")              ;
        break                                                            ;
        default                                                          :
        break                                                            ;
      }                                                                  ;
    break                                                                ;
    case 3                                                               :
      strMsg  = QObject::tr("System resource failure")                   ;
      strMsg += ": "                                                     ;
      switch ( Minor )                                                   {
        case 1                                                           :
          strMsg += QObject::tr("unable to create new threads")          ;
        break                                                            ;
        case 2                                                           :
          strMsg += QObject::tr("unable to allocate buffers")            ;
        break                                                            ;
        default                                                          :
        break                                                            ;
      }                                                                  ;
    break                                                                ;
    case 4                                                               :
      strMsg  = QObject::tr("File system failure")                       ;
      strMsg += ": "                                                     ;
      switch ( Minor )                                                   {
        case 1                                                           :
          strMsg += QObject::tr("cannot seek read position")             ;
        break                                                            ;
        case 2                                                           :
          strMsg += QObject::tr("failure in read")                       ;
        break                                                            ;
        case 3                                                           :
          strMsg += QObject::tr("cannot seek write position")            ;
        break                                                            ;
        case 4                                                           :
          strMsg += QObject::tr("failure in write")                      ;
        break                                                            ;
        default                                                          :
        break                                                            ;
      }                                                                  ;
    break                                                                ;
    case 5                                                               :
      strMsg  = QObject::tr("Operation not supported")                   ;
      strMsg += ": "                                                     ;
      switch ( Minor )                                                   {
        case  1                                                          :
          strMsg += QObject::tr(": Cannot do this operation on a BOUND socket");
        break                                                            ;
        case  2                                                          :
          strMsg += QObject::tr(": Cannot do this operation on a CONNECTED socket");
        break                                                            ;
        case  3                                                          :
          strMsg += QObject::tr(": Bad parameters")                      ;
        break                                                            ;
        case  4                                                          :
          strMsg += QObject::tr(": Invalid socket ID")                   ;
        break                                                            ;
        case  5                                                          :
          strMsg += QObject::tr(": Cannot do this operation on an UNBOUND socket");
        break                                                            ;
        case  6                                                          :
          strMsg += QObject::tr(": Socket is not in listening state")    ;
        break                                                            ;
        case  7                                                          :
          strMsg += QObject::tr(": Listen/accept is not supported in rendezous connection setup");
        break                                                            ;
        case  8                                                          :
          strMsg += QObject::tr(": Cannot call connect on UNBOUND socket in rendezvous connection setup");
        break                                                            ;
        case  9                                                          :
          strMsg += QObject::tr(": This operation is not supported in SOCK_STREAM mode");
        break                                                            ;
        case 10                                                          :
          strMsg += QObject::tr(": This operation is not supported in SOCK_DGRAM mode");
        break                                                            ;
        case 11                                                          :
          strMsg += QObject::tr(": Another socket is already listening on the same port");
        break                                                            ;
        case 12                                                          :
          strMsg += QObject::tr(": Message is too large to send (it must be less than the UDT send buffer size)");
        break                                                            ;
        case 13                                                          :
          strMsg += QObject::tr(": Invalid epoll ID")                    ;
        break                                                            ;
        default                                                          :
        break                                                            ;
      }                                                                  ;
    break                                                                ;
    case 6                                                               :
      strMsg  = QObject::tr("Non-blocking call failure")                 ;
      strMsg += ": "                                                     ;
      switch ( Minor )                                                   {
        case 1                                                           :
          strMsg += QObject::tr("no buffer available for sending")       ;
        break                                                            ;
        case 2                                                           :
          strMsg += QObject::tr("no data available for reading")         ;
        break                                                            ;
        default                                                          :
        break                                                            ;
      }                                                                  ;
    break                                                                ;
    case 7                                                               :
      strMsg = QObject::tr("The peer side has signalled an error")       ;
    break                                                                ;
    default                                                              :
      strMsg = QObject::tr("Unknown error")                              ;
    break                                                                ;
  }                                                                      ;
  // Adding "errno" information
  if ( ( 0 != Major ) && ( 0 < Errno ) )                                 {
    strMsg += ": "                                                       ;
    #ifndef WIN32
    char errmsg[1024]                                                    ;
    if (strerror_r(Errno,errmsg, 1024) == 0) strMsg += errmsg            ;
    #else
    LPVOID lpMsgBuf                                                      ;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER                         |
                  FORMAT_MESSAGE_FROM_SYSTEM                             |
                  FORMAT_MESSAGE_IGNORE_INSERTS                          ,
                  NULL                                                   ,
                  Errno                                                  ,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT)              ,
                  (LPTSTR)&lpMsgBuf                                      ,
                  0                                                      ,
                  NULL                                                 ) ;
    strMsg += QString((char *)lpMsgBuf)                                  ;
    LocalFree(lpMsgBuf)                                                  ;
    #endif
  }                                                                      ;
  // period
  #ifndef WIN32
  strMsg += "."                                                          ;
  #endif
  return (const char *)strMsg.toUtf8().constData()                       ;
}

int N::UDT::Exception::getErrorCode(void) const
{
  return ( ( Major * 1000 ) + Minor ) ;
}

void N::UDT::Exception::clear(void)
{
   Major = 0 ;
   Minor = 0 ;
   Errno = 0 ;
}
