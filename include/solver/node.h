/**
 * @author      Yanqing Wu
 * @email       meet.yanqing.wu@gmail.com
 * @create date 2023-02-10 05:31:05
 * @modify date 2023-03-21 17:59:39
 * @desc Node for Game class
 */
#ifndef FG_SOLVER_NODE_H_
#define FG_SOLVER_NODE_H_
// std
#include <memory>
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
  Node(const Game &game, const helper::Pos &pos, uint8_t value);

  void evaluate(helper::PLAYER player);
  void generateChildren();

  inline Game game() const { return game_; }
  inline int value() const { return eval_val_; }
  inline helper::Move move() const { return move_; }
  inline std::vector<Node> children() const { return children_; }

 protected:
  Game game_;
  bool is_expanded_;
  int eval_val_{};  // evaluation value of the node, can be positive and negative
  helper::Move move_;
  std::vector<Node> children_{};
};

class NodeTT : public Node {
 public:
  explicit NodeTT(const Game &game);
  NodeTT(const Game &game, const helper::Pos &pos, uint8_t value);

  void generateChildren();

  inline std::string id() const { return id_; }
  inline std::vector<NodeTT> children() const { return children_; }

 protected:
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
  Node(const Game &game, const helper::Pos &pos, uint8_t value);

  void generateChildren();

  inline Game game() const { return game_; }
  inline helper::Move move() const { return move_; }
  inline std::vector<Node> children() const { return children_; }

 protected:
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

  inline std::string id() const { return id_; }
  inline std::vector<NodeTT> children() const { return children_; }

 protected:
  std::string id_;
  std::vector<NodeTT> children_{};
};

}  // namespace negamax

/////////////////////////////////////
//  MCTS Node Class
/////////////////////////////////////
namespace mcts {

class Node {
 public:
  explicit Node(const Game &game);
  Node(const Game &game, const helper::Pos &pos, uint8_t value, const std::shared_ptr<Node> &parent = nullptr);
  ~Node() = default;

  inline Game game() const { return game_; }
  inline helper::Move move() const { return move_; }
  inline std::weak_ptr<Node> parent() const { return parent_; }

  size_t visits_ = 1;
  int wins_      = 0;
  std::vector<std::shared_ptr<Node>> children_;

 protected:
  Game game_;
  helper::Move move_;
  std::weak_ptr<Node> parent_{};
};

}  // namespace mcts

}  // namespace solver

#endif  // FG_SOLVER_NODE_H_
