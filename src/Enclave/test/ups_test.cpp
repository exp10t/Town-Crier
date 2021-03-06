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

#include <stdio.h>
#include <stdlib.h>

#include "scrapers/ups_tracking.h"
#include <string>


int ups_self_test() {
  //std::string example_json("{\"id\": \"trk_c8e0edb5bb284caa934a0d3db23a148z\",\"tracking_details\": [{\"object\": \"TrackingDetail\",\"message\": \"Shipping Label Created\",\"status\": \"pre_transit\",\"datetime\": \"2015-12-31T15:58:00Z\",\"source\": \"USPS\",\"tracking_location\": {\"object\": \"TrackingLocation\",\"city\": \"FOUNTAIN VALLEY\",\"state\": \"CA\",\"country\": null,\"zip\": \"92708\"}},{\"object\": \"TrackingDetail\",\"message\": \"Arrived at Post Office\",\"status\": \"in_transit\",\"datetime\": \"2016-01-07T06:58:00Z\",\"source\": \"USPS\",\"tracking_location\": {\"object\": \"TrackingLocation\",\"city\": \"FOUNTAIN VALLEY\",\"state\": \"CA\",\"country\": null,\"zip\": \"92728\"}}]}");

  USPSScraper uspsScraper;
  int resp;
  //std::string status = uspsScraper.parse_response(example_json);
  //LL_INFO("status: %s", status.c_str());
  /* empty strings */ 

  uspsScraper.ups_tracking("EZ2000000002", "USPS", &resp);
  return 0;
}


