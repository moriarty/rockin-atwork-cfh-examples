/*  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the authors nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <protobuf_comm/peer.h>
#include <boost/date_time.hpp>
#include "cfh_msgs.h"

using namespace protobuf_comm;

#define TEAM_NAME    "RoCKInNRoLLIn"
#define ROBOT_NAME   "my_robot"
#define PRIVATE_PORT 4446

class ExamplePeer
{
 public:
  ExamplePeer(std::string host, unsigned short public_port, unsigned short team_port)
    : host_(host), mr_(new MessageRegister()), peer_public_(NULL), peer_team_(NULL), sequence_number_(0)
  {
    mr_->add_message_type<rockin_msgs::BeaconSignal>();
    peer_public_ = setup_peer(public_port);
    peer_team_ = setup_peer(team_port);
  }

  ~ExamplePeer() {
    delete peer_team_;
    delete peer_public_;
  }

  void send_beacon_signal()
  {
    std::shared_ptr<rockin_msgs::BeaconSignal> signal(new rockin_msgs::BeaconSignal());

    // Get the current time of the peer
    boost::posix_time::ptime now(boost::posix_time::microsec_clock::universal_time());
    boost::posix_time::time_duration since_epoch = now - boost::posix_time::from_time_t(0);

    // Add a timestamp to the signal
    rockin_msgs::Time *time = signal->mutable_time();
    time->set_sec(static_cast<google::protobuf::int64>(since_epoch.total_seconds()));
    time->set_nsec(
      static_cast<google::protobuf::int64>(since_epoch.fractional_seconds() * 
             (1000000000/since_epoch.ticks_per_second())));

    // Add the robot's name, peer name and a sequence number to the signal
    signal->set_peer_name(ROBOT_NAME);
    signal->set_team_name(TEAM_NAME);
    signal->set_seq(++sequence_number_);
    peer_team_->send(signal);
  }

 private:
  void peer_recv_error(boost::asio::ip::udp::endpoint &endpoint, std::string msg) {
    std::cout << "Receive error from " << endpoint.address().to_string()
        << ":" << endpoint.port() << ": " << msg << std::endl;
  }

  void peer_send_error(std::string msg) {
    std::cout << "Send error: " << msg << std::endl;
  }

  void peer_msg(boost::asio::ip::udp::endpoint &endpoint, uint16_t comp_id, uint16_t msg_type,
    std::shared_ptr<google::protobuf::Message> msg)
  {
    std::shared_ptr<rockin_msgs::BeaconSignal> b;
    if ((b = std::dynamic_pointer_cast<rockin_msgs::BeaconSignal>(msg))) {
      std::cout << "Beacon signal received" << std::endl;
    }
  }

  ProtobufBroadcastPeer * setup_peer(unsigned short int port) {
    ProtobufBroadcastPeer *peer = new ProtobufBroadcastPeer(host_, port, mr_);
    peer->signal_recv_error().connect(
      boost::bind(&ExamplePeer::peer_recv_error, this, _1, _2));
    peer->signal_send_error().connect(
      boost::bind(&ExamplePeer::peer_send_error, this, _1));
    peer->signal_received().connect(
      boost::bind(&ExamplePeer::peer_msg, this, _1, _2, _3, _4));
    return peer;
  }

 private:
  std::string            host_;
  MessageRegister       *mr_;
  ProtobufBroadcastPeer *peer_public_;
  ProtobufBroadcastPeer *peer_team_;
  unsigned long          sequence_number_;
};

int main(int argc, char **argv) {
  ExamplePeer peer("192.168.1.100", 4444, 4446);
  peer.send_beacon_signal();
  while (true) usleep(100000);
}

