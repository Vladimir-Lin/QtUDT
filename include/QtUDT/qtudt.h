/****************************************************************************
 *                                                                          *
 * Copyright (C) 2015 Neutrino International Inc.                           *
 *                                                                          *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin            *
 *                                                                          *
 ****************************************************************************/

#ifndef QT_UDT_H
#define QT_UDT_H

#include <QtCore>
#include <QtNetwork>
#include <QtScript>
#include <Essentials>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_QTUDT_LIB)
#      define Q_UDT_EXPORT Q_DECL_EXPORT
#    else
#      define Q_UDT_EXPORT Q_DECL_IMPORT
#    endif
#else
#    define Q_UDT_EXPORT
#endif

namespace N   {
namespace UDT {

/*****************************************************************************\
 *                                                                           *
 *                  UDP-based Data Transfer Protocol / UDT                   *
 *                                                                           *
\*****************************************************************************/

class Q_UDT_EXPORT PerformanceMonitor ;
class Q_UDT_EXPORT Exception          ;
class Q_UDT_EXPORT SequenceNo         ;
class Q_UDT_EXPORT AckNo              ;
class Q_UDT_EXPORT MessageNo          ;

class Q_UDT_EXPORT PerformanceMonitor
{
  public:

    explicit PerformanceMonitor (void) ;
    virtual ~PerformanceMonitor (void) ;

   // global measurements
   TUID   msTimeStamp         ; // time since the UDT entity is started, in milliseconds
   TUID   pktSentTotal        ; // total number of sent data packets, including retransmissions
   TUID   pktRecvTotal        ; // total number of received packets
   int    pktSndLossTotal     ; // total number of lost packets (sender side)
   int    pktRcvLossTotal     ; // total number of lost packets (receiver side)
   int    pktRetransTotal     ; // total number of retransmitted packets
   int    pktSentACKTotal     ; // total number of sent ACK packets
   int    pktRecvACKTotal     ; // total number of received ACK packets
   int    pktSentNAKTotal     ; // total number of sent NAK packets
   int    pktRecvNAKTotal     ; // total number of received NAK packets
   TUID   usSndDurationTotal  ; // total time duration when UDT is sending data (idle time exclusive)

   // local measurements
   TUID   pktSent             ; // number of sent data packets, including retransmissions
   TUID   pktRecv             ; // number of received packets
   int    pktSndLoss          ; // number of lost packets (sender side)
   int    pktRcvLoss          ; // number of lost packets (receiver side)
   int    pktRetrans          ; // number of retransmitted packets
   int    pktSentACK          ; // number of sent ACK packets
   int    pktRecvACK          ; // number of received ACK packets
   int    pktSentNAK          ; // number of sent NAK packets
   int    pktRecvNAK          ; // number of received NAK packets
   double mbpsSendRate        ; // sending rate in Mb/s
   double mbpsRecvRate        ; // receiving rate in Mb/s
   TUID   usSndDuration       ; // busy sending time (i.e., idle time exclusive)

   // instant measurements
   double usPktSndPeriod      ; // packet sending period, in microseconds
   int    pktFlowWindow       ; // flow window size, in number of packets
   int    pktCongestionWindow ; // congestion window size, in number of packets
   int    pktFlightSize       ; // number of packets on flight
   double msRTT               ; // RTT, in milliseconds
   double mbpsBandwidth       ; // estimated bandwidth, in Mb/s
   int    byteAvailSndBuf     ; // available UDT sender buffer size
   int    byteAvailRcvBuf     ; // available UDT receiver buffer size

  protected:

  private:

};

class Q_UDT_EXPORT Exception
{
  public:

    // Error Code
    static const int SUCCESS      ;
    static const int ECONNSETUP   ;
    static const int ENOSERVER    ;
    static const int ECONNREJ     ;
    static const int ESOCKFAIL    ;
    static const int ESECFAIL     ;
    static const int ECONNFAIL    ;
    static const int ECONNLOST    ;
    static const int ENOCONN      ;
    static const int ERESOURCE    ;
    static const int ETHREAD      ;
    static const int ENOBUF       ;
    static const int EFILE        ;
    static const int EINVRDOFF    ;
    static const int ERDPERM      ;
    static const int EINVWROFF    ;
    static const int EWRPERM      ;
    static const int EINVOP       ;
    static const int EBOUNDSOCK   ;
    static const int ECONNSOCK    ;
    static const int EINVPARAM    ;
    static const int EINVSOCK     ;
    static const int EUNBOUNDSOCK ;
    static const int ENOLISTEN    ;
    static const int ERDVNOSERV   ;
    static const int ERDVUNBOUND  ;
    static const int ESTREAMILL   ;
    static const int EDGRAMILL    ;
    static const int EDUPLISTEN   ;
    static const int ELARGEMSG    ;
    static const int EINVPOLLID   ;
    static const int EASYNCFAIL   ;
    static const int EASYNCSND    ;
    static const int EASYNCRCV    ;
    static const int ETIMEOUT     ;
    static const int EPEERERR     ;
    static const int EUNKNOWN     ;

    explicit Exception (int major = 0,int minor = 0,int err = -1) ;
             Exception (const Exception & e) ;
    virtual ~Exception(void);

      // Functionality:
      //    Get the description of the exception.
      // Parameters:
      //    None.
      // Returned value:
      //    Text message for the exception description.

    virtual const char * getErrorMessage (void) ;

      // Functionality:
      //    Get the system errno for the exception.
      // Parameters:
      //    None.
      // Returned value:
      //    errno.

    virtual int getErrorCode (void) const ;

      // Functionality:
      //    Clear the error code.
      // Parameters:
      //    None.
      // Returned value:
      //    None.

    virtual void clear (void);

  protected:

  private:

    int    Major    ; // major exception categories
                      // 0: correct condition
                      // 1: network setup exception
                      // 2: network connection broken
                      // 3: memory exception
                      // 4: file exception
                      // 5: method not supported
                      // 6+: undefined error
   int     Minor    ; // for specific error reasons
   int     Errno    ; // errno returned by the system if there is any
   QString strMsg   ; // text error message

   QString strAPI   ; // the name of UDT function that returns the error
   QString strDebug ; // debug information, set to the original place that causes the error

};

// UDT Sequence Number 0 - (2^31 - 1)
// seqcmp: compare two seq#, considering the wraping
// seqlen: length from the 1st to the 2nd seq#, including both
// seqoff: offset from the 2nd to the 1st seq#
// incseq: increase the seq# by 1
// decseq: decrease the seq# by 1
// incseq: increase the seq# by a given offset

class Q_UDT_EXPORT SequenceNo
{
  public:

    explicit SequenceNo (void) ;
    virtual ~SequenceNo (void) ;

    static const int SeqNoTH  ; // threshold for comparing seq. no.
    static const int MaxSeqNo ; // maximum sequence number used in UDT

    static int seqcmp (int seq1,int seq2) ;
    static int seqlen (int seq1,int seq2) ;
    static int seqoff (int seq1,int seq2) ;
    static int incseq (int seq ,int inc ) ;
    static int incseq (int seq) ;
    static int decseq (int seq) ;

  protected:

  private:

};

class Q_UDT_EXPORT AckNo
{
  public:

    explicit AckNo (void) ;
    virtual ~AckNo (void) ;

    static const int MaxAckSeqNo ; // maximum ACK sub-sequence number used in UDT

    static int incack(int ackno) ;

  protected:

  private:

};

// UDT Message Number: 0 - (2^29 - 1)

class Q_UDT_EXPORT MessageNo
{
  public:

    explicit MessageNo (void) ;
    virtual ~MessageNo (void) ;

    static const int MsgNoTH  ; // threshold for comparing msg. no.
    static const int MaxMsgNo ; // maximum message number used in UDT

    static int msgcmp(int msgno1,int msgno2) ;
    static int msglen(int msgno1,int msgno2) ;
    static int msgoff(int msgno1,int msgno2) ;
    static int incmsg(int msgno) ;

  protected:

  private:

};

}
}

Q_DECLARE_METATYPE(N::UDT::PerformanceMonitor)
Q_DECLARE_METATYPE(N::UDT::Exception)
Q_DECLARE_METATYPE(N::UDT::SequenceNo)
Q_DECLARE_METATYPE(N::UDT::AckNo)
Q_DECLARE_METATYPE(N::UDT::MessageNo)

QT_END_NAMESPACE

#endif
