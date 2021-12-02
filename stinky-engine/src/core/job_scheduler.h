//
// Created by christian on 7/27/21.
//

#ifndef STINKY_JOB_SCHEDULER_H
#define STINKY_JOB_SCHEDULER_H

#include <condition_variable>
#include <list>

#include "core/Time.h"

namespace stinky {

template <class job_id> struct job {
  using job_function = std::function<void()>;
  job_id id;
  job_function job;
  time_frame execute_at;
};

template <class job_id> class job_scheduler {
public:
  job_scheduler() = default;
  ~job_scheduler() = default;

public:
  void update(const time_frame &ts) {
    {
      std::unique_lock<std::mutex> lock(update_mutex);
      updated = true;
    }

    update_conditional_variable.notify_one();
  }

  void operator()() {
    {
      std::unique_lock<std::mutex> lock(update_mutex);
      update_conditional_variable.wait(update_mutex,
                                       [&updated]() { return updated });
    }

    time_frame now(std::move(time_frame::now()));
    for (auto jobs_it = jobs.begin();
         jobs_it != jobs.end() && now > jobs_it->execute_at;
         jobs_it = jobs.erase(jobs_it)) {
      jobs_it->job();
    }
  }

  void enqueue(job_id id, job::job_function job, const time_frame &execute_at) {
    jobs.emplace_back(id, job, execute_at);
  }

private:
  std::mutex update_mutex;
  std::conditional_variable update_conditional_variable;
  bool updated = false;

private:
  std::list<job<job_id>> jobs;
};
} // namespace stinky

#endif // STINKY_JOB_SCHEDULER_H
