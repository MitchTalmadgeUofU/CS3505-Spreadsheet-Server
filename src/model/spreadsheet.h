#ifndef PIGRAMMERS_SPREADSHEET_SERVER_SPREADSHEET_H
#define PIGRAMMERS_SPREADSHEET_SERVER_SPREADSHEET_H

#include <string>
#include <map>
#include <stack>
#include <fstream>
#include <boost/optional/optional.hpp>

/**
 * Simple struct to hold the value of a cell at a given time.
 * Used by undo/revert functionality to maintain cell/spreadsheet
 * history.
 */
struct cell_history {
  std::string cell_name;
  std::string contents;
  bool is_revert;
};

/**
 * Represents one collaborative Spreadsheet and all its contents.
 */
class spreadsheet {

  /**
   * Determines if the spreadsheet is loaded and able to be used.
   * If reading from a file fails, this will be false. The default constructor will always have this be true.
   */
  bool loaded_;

  /**
   * Contains the contents of each cell in the spreadsheet.
   * Maps cell names to cell contents.
   */
  std::map<std::string, std::string> cell_contents_;

  /**
   * Maps socket IDs to the names of their focused cells.
   * If a socket is not focusing on a cell, they will not have a key in this map.
   */
  std::map<int, std::string> focused_cells_;

  /**
   * Hold history of values across spreadsheet to allow undo functionality.
   */
  std::stack<cell_history> undo_history_;

  /**
   * Hold cell specific history.
   */
  std::map<std::string, std::stack<std::string>> revert_history_;

 public:

  /**
   * Creates a new, empty spreadsheet.
   */
  spreadsheet();

  /**
   * Loads a spreadsheet from a file.
   * @param file_path The path to the JSON spreadsheet file.
   */
  explicit spreadsheet(const std::string &file_path);

  bool is_loaded() const;

  /**
   * Saves this spreadsheet to a JSON file.
   * After a successful save, the spreadsheet is no longer considered "changed."
   * @param file_path Where to save the spreadsheet, including the file's name and extension.
   */
  void save_to_file(const std::string &file_path);

  /**
   * Retrieves the contents of a specific cell.
   * @param cell_name The name of the cell.
   * @return The contents of the cell.
   */
  std::string get_cell_contents(const std::string &cell_name) const;

  /**
   * Sets the contents of a specific cell.
   * @param cell_name The name of the cell.
   * @param contents The contents of the cell.
   */
  void set_cell_contents(const std::string &cell_name, const std::string &contents);

  /**
   * @return A map containing cell names mapped to contents for all cells which have non-empty contents.
   */
  std::map<std::string, std::string> get_non_empty_cells() const;

  /**
   * @return A map containing socket ids mapped to the cell that client is focusing.
   */
  std::map<int, std::string> get_focused_cells() const;

  /**
   * Marks a client as having focused on a particular cell.
   * @param socket_id The ID of the socket representing the client that is focusing on a cell.
   * @param cell_name The name of the cell to focus on.
   */
  void focus_cell(int socket_id, const std::string &cell_name);

  /**
   * Removes any focuses for a particular client.
   * @param socket_id The ID of the socket representing the client that is no longer focusing on a cell.
   */
  void unfocus_cell(int socket_id);

  /**
   * Undo the most recent edit action (i.e., edit message from client or revert).
   * @return The updated cell name and contents as a result of the undo.
   */
  boost::optional<std::pair<std::string, std::string> > undo();

  /**
   * Revert the most recent edit action for the specified cell.
   * @return The updated cell name and contents as a result of the revert.
   */
  boost::optional<std::pair<std::string, std::string> > revert(const std::string &cell_name);

};

#endif //PIGRAMMERS_SPREADSHEET_SERVER_SPREADSHEET_H
