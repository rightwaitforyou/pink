#include "holy_test.h"
#include "xdebug.h"

#include "holy_thread.h"
#include <functional>
#include <string>
#include "pink.pb.h"
#include "pb_conn.h"

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>

PinkHolyConn::PinkHolyConn(int fd, Thread *thread) :
  PbConn(fd)
{
  
  pink_thread_ = reinterpret_cast<PinkThread *>(thread);

}

int PinkHolyConn::DealMessage()
{

  log_info("In the PinkHolyConn DealMessage branch");
  ping_.ParseFromArray(rbuf_ + 4, header_len_);
  
  printf("%s %d\n", ping_.address().data(), ping_.port());

  pink_thread_->v.push_back(123);

  printf("pink_thread vestor size %d", pink_thread_->v.size());
  pingRes_.set_res(11234);
  pingRes_.set_mess("heiheidfdfdf");

  res_ = &pingRes_;

  int wbuf_len_ = res_->ByteSize();

  return 0;
}



PinkThread::PinkThread(int port) :
  HolyThread<PinkHolyConn>(port)
{

}


PinkThread::~PinkThread()
{

}