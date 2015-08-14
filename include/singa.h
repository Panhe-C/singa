#ifndef SINGA_SINGA_H_
#define SINGA_SINGA_H_

#include <cblas.h>
#include <glog/logging.h>
#include <string>
#include "communication/socket.h"
#include "neuralnet/neuralnet.h"
#include "proto/job.pb.h"
#include "proto/singa.pb.h"
#include "trainer/trainer.h"
#include "utils/common.h"
#include "utils/param.h"
#include "utils/singleton.h"
#include "utils/factory.h"

namespace singa {

class Driver {
 public:
  /**
   * Init SINGA, including init glog, parse job id and job conf from cmd line,
   * and register built-in layer, worker, updater, param subclasses.
   *
   * May be used for MPI init if it is used for message passing.
   */
  void Init(int argc, char** argv);
  /**
   * Register a Layer subclass.
   *
   * T is the subclass.
   * @param type layer type ID. If called by users, it should be different to
   * the types of built-in layers.
   * @return 0 if success; otherwise -1.
   */
  template<typename T>
  int RegisterLayer(int type);
  /**
   * Register Updater subclasses.
   *
   * T is the subclass.
   * @param type updater type ID. If called by users, it should be different to
   * the types of built-in updaters.
   * @return 0 if success; otherwise -1.
   */
  template<typename T>
  int RegisterUpdater(int type);
  /**
   * Register Worker subclasses.
   *
   * T is the subclass.
   * @param type worker type ID. If called by users, it should be different to
   * the types of built-in workers
   * @return 0 if success; otherwise -1.
   */
  template<typename T>
  int RegisterWorker(int type);
  /**
   * Register Param subclasses.
   *
   * T is the subclass.
   * @param type param type. If called by users, it should be different to the
   * types of built-in params. SINGA currently provides only one built-in Param
   * implementation whose type ID is 0.
   * @return 0 if success; otherwise -1.
   */
  template<typename T>
  int RegisterParam(int type);
  /**
   * Submit the job configuration for starting the job.
   * @param resume resume from last checkpoint if true.
   * @param job job configuration
   */
  void Submit(bool resume, const JobProto& job);
  /**
   * @return job ID which is generated by zookeeper and passed in by the
   * launching script.
   */
  inline int job_id() const { return job_id_; }
  /**
   * @return job conf path which is passed by users at the command line. It
   * should at least contains the cluster configuration.
   */
  inline JobProto job_conf() const { return job_conf_; }

 private:
  int job_id_;
  JobProto job_conf_;
  SingaProto singa_conf_;
};

}  // namespace singa

#endif  // SINGA_SINGA_H_
