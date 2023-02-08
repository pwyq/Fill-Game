#pragma once

#include <unordered_map>
#include <utility>

#include "node.h"

namespace Solver
{

    
extern size_t g_counter;

class DFPN {
public:
    Node root;
    PROOF_VALUE result = UNKNOWN;
    Move best_move;

    explicit DFPN(const Game& game);

    void solve();

    void MID(Node& node);

    size_t selectChild(Node& node, uint32_t& child_phi, uint32_t& delta_2);

    std::string formatResult() const;

    static void signalHandler([[maybe_unused]] int signum);

private:
    std::unordered_map<std::string, std::pair<uint32_t, uint32_t>> tt;

    void saveProofAndDisproofNumbers(Node& node, uint32_t phi, uint32_t delta);

    void retrieveProofAndDisproofNumbers(Node& node, uint32_t& phi, uint32_t& delta);

    uint32_t computeMinDelta(Node& node);

    uint32_t computeSumPhi(Node& node);
};


} // namespace Solver


