/**
 * @file peer_message_sender.hpp
 *
 * Project Clearwater - IMS in the Cloud
 * Copyright (C) 2014  Metaswitch Networks Ltd
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version, along with the "Special Exception" for use of
 * the program along with SSL, set forth below. This program is distributed
 * in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details. You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * The author can be reached by email at clearwater@metaswitch.com or by
 * post at Metaswitch Networks Ltd, 100 Church St, Enfield EN2 6BQ, UK
 *
 * Special Exception
 * Metaswitch Networks Ltd  grants you permission to copy, modify,
 * propagate, and distribute a work formed by combining OpenSSL with The
 * Software, or a work derivative of such a combination, even if such
 * copying, modification, propagation, or distribution would otherwise
 * violate the terms of the GPL. You must comply with the GPL in all
 * respects for all of the code used other than OpenSSL.
 * "OpenSSL" means OpenSSL toolkit software distributed by the OpenSSL
 * Project and licensed under the OpenSSL Licenses, or a work based on such
 * software and licensed under the OpenSSL Licenses.
 * "OpenSSL Licenses" means the OpenSSL License and Original SSLeay License
 * under which the OpenSSL Project distributes the OpenSSL toolkit software,
 * as those licenses appear in the file LICENSE-OPENSSL.
 */
#ifndef PEER_MESSAGE_SENDER_HPP_
#define PEER_MESSAGE_SENDER_HPP_

#include <freeDiameter/freeDiameter-host.h>
#include <freeDiameter/libfdcore.h>

#include "rf.h"
#include "message.hpp"
#include "session_manager.hpp"

// A PeerMessageSender is responsible for ensuring that a connection is open
// to either the primary or backup CCF, and once a connection has been opened,
// sending the message to it.
class PeerMessageSender
{
public:
  PeerMessageSender(SAS::TrailId trail, const std::string& dest_realm);
  virtual ~PeerMessageSender();
  virtual void send(Message* msg,
                    SessionManager* sm,
                    Rf::Dictionary* dict,
                    Diameter::Stack* diameter_stack);

  void send_cb(int result_cdoe, int interim_interval, std::string session_id);

private:
  void int_send_msg();

  Message* _msg;
  unsigned int _which;
  std::vector<std::string> _ccfs;
  SessionManager* _sm;
  Rf::Dictionary* _dict;
  Diameter::Stack* _diameter_stack;
  SAS::TrailId _trail;
  const std::string _dest_realm;
};

#endif /* PEER_MESSAGE_SENDER_HPP_ */
