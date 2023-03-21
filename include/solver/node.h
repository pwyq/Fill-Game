/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:31:05
 * @modify date 2023-03-21 15:23:08
 * @desc Node for Game class
 */
#ifndef FG_SOLVER_NODE_H_
#define FG_SOLVER_NODE_H_
// local
#include "game.h"

namespace solver {

/////////////////////////////////////
//  Basic Node Class
/////////////////////////////////////
// TODO: generalize?
// class Node {
//  public:
//   Node();
// };

/////////////////////////////////////
//  PNS Node Class
/////////////////////////////////////

// see include/solver/pns_node.h

/////////////////////////////////////
//  DFPN Node Class
/////////////////////////////////////
namespace dfpn {
class Node {
 public:
  explicit Node(const Game &game);
  Node(const Game &game, const helper::Pos &pos, uint8_t value);

  void evaluate();
  void generateChildren();

  Game game_;
  uint32_t phi_;
  uint32_t delta_;
  bool is_expanded_;

  helper::Move move_;
  std::string id_;
  std::vector<Node> children_{};
};
}  // namespace dfpn

/////////////////////////////////////
//  Minimax Node Class
/////////////////////////////////////
namespace minimax {
class Node {
 public:
  explicit Node(const Game &game);
  virtual ~Node() = default;
  Node(const Game &game, const helper::Pos &pos, uint8_t value);

  void evaluate(helper::PLAYER player);
  void generateChildren();

  Game game_;
  bool is_expanded_;

  int eval_val_{};  // evaluation value of the node, can be positive and negative
  helper::Move move_;
  std::vector<Node> children_{};
};

class NodeTT : public Node {
 public:
  explicit NodeTT(const Game &game);
  virtual ~NodeTT() = default;
  NodeTT(const Game &game, const helper::Pos &pos, uint8_t value);

  void generateChildren();

  std::string id_;
  std::vector<NodeTT> children_{};
};

}  // namespace minimax

/////////////////////////////////////
//  Negamax Node Class
//    TODO: how can we use template<> for the children vector such that it takes both `Node` and `NodeTT`?
/////////////////////////////////////
namespace negamax {
class Node {
 public:
  explicit Node(const Game &game);
  virtual ~Node() = default;
  Node(const Game &game, const helper::Pos &pos, uint8_t value);

  void generateChildren();

  Game game_;
  bool is_expanded_;

  helper::Move move_;
  std::vector<Node> children_{};
};

class NodeTT : public Node {
 public:
  explicit NodeTT(const Game &game);
  NodeTT(const Game &game, const helper::Pos &pos, uint8_t value);

  void generateChildren();

  std::string id_;
  std::vector<NodeTT> children_{};
};

}  // namespace negamax

}  // namespace solver

#endif  // FG_SOLVER_NODE_H_
