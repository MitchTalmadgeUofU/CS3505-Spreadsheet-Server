/*
network_controller.h

Network Controller handles maintaining connections and communication with connected
clients.
 */

#ifndef PIGRAMMERS_SPREADSHEET_SERVER_NETWORK_CONTROLLER
#define PIGRAMMERS_SPREADSHEET_SERVER_NETWORK_CONTROLLER

#include <map>
#include <vector>
#include <string>
#include <boost/thread/thread.hpp>
#include <functional>
#include <controller/data_container.h>

class network_controller {

 private:

  /**
   * End of Text terminator.
   */
  static const std::string EOT;

  /**
   * Milliseconds between pings.
   */
  static const int ping_time = 10000;

  /**
   * Milliseconds for timeout if no response from connected client.
   */
  static const int ping_timeout = 60000;

  /**
   * Data container is where outgoing messages will be stored.
   */
  data_container &data_container_ = data_container::get_instance();

  /**
   * Maintain list of worker threads to allow shutting down.
   */
  std::vector<boost::thread*> worker_threads_;

  /** 
   * Work loop for the network controller, where it listens in on a socket for incoming
   * messages.
   */
  void socket_work_loop(int socket_id);

  /**
   * Private constructor for singleton pattern.
   */
  network_controller();

  /**
   * Private destructor for singleton pattern.
   */
  ~network_controller();

 public:

  /**
   * Set the blocking settings of the socket.
   *
   * @param socket_id File descriptor of socket.
   * @param blocking Whether the socket should be set to blocking.
   * @return true if successful, false otherwise.
   */
  static bool set_socket_block_state(int socket_id, bool blocking);

  /**
   * @return The singleton instance of this controller.
   */
  static network_controller &get_instance();

  /**
   * Deleted copy constructor since this is a singleton.
   */
  network_controller(network_controller const &) = delete;

  /**
   * Deleted assignment operator since this is a singleton.
   */
  void operator=(network_controller const &)  = delete;

  /**
   * Create a work loop for the provided socket.
   */
  void start_work(int socket_id);

};

#endif
