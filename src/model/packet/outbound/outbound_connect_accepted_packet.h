#ifndef PIGRAMMERS_SPREADSHEET_SERVER_OUTBOUND_CONNECT_ACCEPTED_PACKET_H
#define PIGRAMMERS_SPREADSHEET_SERVER_OUTBOUND_CONNECT_ACCEPTED_PACKET_H

#include <set>
#include "outbound_packet.h"

class outbound_connect_accepted_packet : public outbound_packet {

  /**
   * Contains the names of all existing spreadsheets that may be loaded by a client.
   */
  const std::set<std::string> spreadsheet_names_;

 public:

  explicit outbound_connect_accepted_packet(const std::set<std::string> &spreadsheet_names);

  outbound_packet *clone() const override;

  outbound_packet_type get_packet_type() override;

  std::string get_raw_message() override;

  const std::set<std::string> &get_spreadsheet_names() const;

};

#endif //PIGRAMMERS_SPREADSHEET_SERVER_OUTBOUND_CONNECT_ACCEPTED_PACKET_H
