/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVELEDGER_ENDPOINT_PROMOTION_POST_BAT_LOSS_POST_BAT_LOSS_H_
#define BRAVELEDGER_ENDPOINT_PROMOTION_POST_BAT_LOSS_POST_BAT_LOSS_H_

#include <string>

#include "bat/ledger/ledger.h"

// POST /v1/wallets/{payment_id}/events/batloss/{version}
//
// Request body:
// {
//   "amount": 20.5
// }
//
// Success code:
// HTTP_OK (200)
//
// Error Codes:
// HTTP_INTERNAL_SERVER_ERROR (500)
//
// Response body:
// {Empty}

namespace bat_ledger {
class LedgerImpl;
}

namespace ledger {
namespace endpoint {
namespace promotion {

using PostBatLossCallback = std::function<void(const ledger::Result result)>;

class PostBatLoss {
 public:
  explicit PostBatLoss(bat_ledger::LedgerImpl* ledger);
  ~PostBatLoss();

  void Request(
      const double amount,
      const int32_t version,
      PostBatLossCallback callback);

 private:
  std::string GetUrl(const int32_t version);

  std::string GeneratePayload(const double amount);

  ledger::Result CheckStatusCode(const int status_code);

  void OnRequest(
      const ledger::UrlResponse& response,
      PostBatLossCallback callback);

  bat_ledger::LedgerImpl* ledger_;  // NOT OWNED
};

}  // namespace promotion
}  // namespace endpoint
}  // namespace ledger

#endif  // BRAVELEDGER_ENDPOINT_PROMOTION_POST_BAT_LOSS_POST_BAT_LOSS_H_
