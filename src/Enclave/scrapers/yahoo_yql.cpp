//
// Copyright (c) 2016-2017 by Cornell University.  All Rights Reserved.
//
// Permission to use the "TownCrier" software ("TownCrier"), officially
// docketed at the Center for Technology Licensing at Cornell University
// as D-7364, developed through research conducted at Cornell University,
// and its associated copyrights solely for educational, research and
// non-profit purposes without fee is hereby granted, provided that the
// user agrees as follows:
//
// The permission granted herein is solely for the purpose of compiling
// the TownCrier source code. No other rights to use TownCrier and its
// associated copyrights for any other purpose are granted herein,
// whether commercial or non-commercial.
//
// Those desiring to incorporate TownCrier software into commercial
// products or use TownCrier and its associated copyrights for commercial
// purposes must contact the Center for Technology Licensing at Cornell
// University at 395 Pine Tree Road, Suite 310, Ithaca, NY 14850; email:
// ctl-connect@cornell.edu; Tel: 607-254-4698; FAX: 607-254-5454 for a
// commercial license.
//
// IN NO EVENT SHALL CORNELL UNIVERSITY BE LIABLE TO ANY PARTY FOR
// DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES,
// INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF TOWNCRIER AND ITS
// ASSOCIATED COPYRIGHTS, EVEN IF CORNELL UNIVERSITY MAY HAVE BEEN
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// THE WORK PROVIDED HEREIN IS ON AN "AS IS" BASIS, AND CORNELL
// UNIVERSITY HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
// ENHANCEMENTS, OR MODIFICATIONS.  CORNELL UNIVERSITY MAKES NO
// REPRESENTATIONS AND EXTENDS NO WARRANTIES OF ANY KIND, EITHER IMPLIED
// OR EXPRESS, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, OR THAT THE USE
// OF TOWNCRIER AND ITS ASSOCIATED COPYRIGHTS WILL NOT INFRINGE ANY
// PATENT, TRADEMARK OR OTHER RIGHTS.
//
// TownCrier was developed with funding in part by the National Science
// Foundation (NSF grants CNS-1314857, CNS-1330599, CNS-1453634,
// CNS-1518765, CNS-1514261), a Packard Fellowship, a Sloan Fellowship,
// Google Faculty Research Awards, and a VMWare Research Award.
//

//
// Created by fanz on 4/12/17.
//
#include <map>

#include "tls_client.h"
#include "yahoo_yql.h"
#include "Scraper.h"
#include "scraper_utils.h"
#include "Log.h"

err_code YahooYQL::execute(string &result) {
  string query = this->buildQuery();
  HttpRequest http_request("query.yahooapis.com", query, true);
  HttpsClient https_client(http_request);

  try {
    HttpResponse response = https_client.getResponse();
    LL_DEBUG("httpStatus=%d", response.getStatusCode());
    result = response.getContent();
    return NO_ERROR;
  } catch (std::runtime_error &e) {
    /* An HTTPS error has occured */
    LL_CRITICAL("Https error: %s", e.what());
    LL_CRITICAL("Details: %s", https_client.getError().c_str());
    https_client.close();
    return WEB_ERROR;
  }
}

string YahooYQL::buildQuery() {
  if (q.empty()) {
    throw invalid_argument("q is empty");
  }

  const string api_prefix = "/v1/public/yql?";
  map<string, string> parameters;

  parameters["q"] = url_encode(q.c_str());
  parameters["format"] = string(format == JSON ? "json" : "xml");
  parameters["diagnostics"] = "false";

  if (!env.empty()) {
    parameters["env"] = url_encode(env.c_str());
  }

  string query;

  for (map<string, string>::iterator it = parameters.begin(); it != parameters.end(); it++) {
    query += (query.empty() ? "" : "&") + (it->first + "=" + it->second);
  }

  return api_prefix + query;
}
