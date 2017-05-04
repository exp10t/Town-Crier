/* * Copyright (c) 2016-2017 by Cornell University.  All Rights Reserved.
 *
 * Permission to use the "TownCrier" software ("TownCrier"), officially
 * docketed at the Center for Technology Licensing at Cornell University
 * as D-7364, developed through research conducted at Cornell University,
 * and its associated copyrights solely for educational, research and
 * non-profit purposes without fee is hereby granted, provided that the
 * user agrees as follows:
 *
 * The permission granted herein is solely for the purpose of compiling
 * the TowCrier source code. No other rights to use TownCrier and its
 * associated copyrights for any other purpose are granted herein,
 * whether commercial or non-commercial.
 *
 * Those desiring to incorporate TownCrier software into commercial
 * products or use TownCrier and its associated copyrights for commercial
 * purposes must contact the Center for Technology Licensing at Cornell
 * University at 395 Pine Tree Road, Suite 310, Ithaca, NY 14850; email:
 * ctl-connect@cornell.edu; Tel: 607-254-4698; FAX: 607-254-5454 for a
 * commercial license.
 *
 * IN NO EVENT SHALL CORNELL UNIVERSITY BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES,
 * INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF TOWNCRIER AND ITS
 * ASSOCIATED COPYRIGHTS, EVEN IF CORNELL UNIVERSITY MAY HAVE BEEN
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE WORK PROVIDED HEREIN IS ON AN "AS IS" BASIS, AND CORNELL
 * UNIVERSITY HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
 * ENHANCEMENTS, OR MODIFICATIONS.  CORNELL UNIVERSITY MAKES NO
 * REPRESENTATIONS AND EXTENDS NO WARRANTIES OF ANY KIND, EITHER IMPLIED
 * OR EXPRESS, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, OR THAT THE USE
 * OF TOWNCRIER AND ITS ASSOCIATED COPYRIGHTS WILL NOT INFRINGE ANY
 * PATENT, TRADEMARK OR OTHER RIGHTS.
 *
 * TownCrier was developed with funding in part by the National Science
 * Foundation (NSF grants CNS-1314857, CNS-1330599, CNS-1453634,
 * CNS-1518765, CNS-1514261), a Packard Fellowship, a Sloan Fellowship,
 * Google Faculty Research Awards, and a VMWare Research Award.
 */

#ifndef SRC_APP_CONFIG_H_
#define SRC_APP_CONFIG_H_

#include <string>

using std::string;

namespace tc {

class Config {
 private:
  const bool DFT_STATUS_ENABLED = false;
  const bool DFT_RUN_AS_DAEMON = false;
  const string DFT_CONFIG_FILE = "config";
  const string DFT_WORKING_DIR = "/tmp/tc";

 public:
  bool is_status_server_enabled() const;
  bool is_run_as_daemon() const;
  const string &get_config_file() const;
  const string &get_working_dir() const;
  const string &get_geth_rpc_addr() const;
  int get_status_server_port() const;
  const string &get_pid_filename() const;
  const string &get_sealed_sig_key() const;
  const string &get_enclave_path() const;
  const string &get_home_dir() const;
  const string &get_current_dir() const;

 private:
  bool opt_status_enabled;
  bool opt_run_as_daemon;
  string opt_config_file;
  string opt_working_dir;

  string cfg_geth_rpc_addr;
  int cfg_status_port;
  string cfg_pid_fn;
  string cfg_sealed_sig_key;
  string cfg_enclave_path;

  string current_dir;
  string home_dir;

 public:
  Config(int argc, const char *argv[]);
  string to_string();
};

}  // namespace tc

#endif  // SRC_APP_CONFIG_H_