// Copyright (c) 2014-2018 Zano Project
// Copyright (c) 2014-2018 The Louisdor Project
// Copyright (c) 2012-2013 The Boolberry developers
// Copyright (c) 2017-2025 Lethean (https://lt.hn)
//
// Licensed under the European Union Public Licence (EUPL) version 1.2.
// You may obtain a copy of the licence at:
//
//     https://joinup.ec.europa.eu/software/page/eupl/licence-eupl
//
// The EUPL is a copyleft licence that is compatible with the MIT/X11
// licence used by the original projects; the MIT terms are therefore
// considered “grandfathered” under the EUPL for this code.
//
// SPDX‑License‑Identifier: EUPL-1.2
//

#pragma once 

#include <thread>
#include <string>
#include <boost/thread.hpp>

namespace utils
{

  struct call_executor_base
  {
    virtual void execute() = 0;
  };

  template<typename t_executor_func>
  struct call_executor_t : public call_executor_base
  {
    call_executor_t(t_executor_func f) :m_func(f)
    {}
    t_executor_func m_func;
    virtual void execute()
    {
      m_func();
    }
  };

  template<typename t_executor_func>
  std::shared_ptr<call_executor_base> build_call_executor(t_executor_func func)
  {
    std::shared_ptr<call_executor_base> res(static_cast<call_executor_base*>(new call_executor_t<t_executor_func>(func)));
    return res;
  }

  class threads_pool
  {
  public:
    typedef std::list<std::shared_ptr<call_executor_base>> jobs_container;

    template<typename t_executor_func>
    static void add_job_to_container(jobs_container& cntr, t_executor_func func)
    {
      cntr.push_back(std::shared_ptr<call_executor_base>(static_cast<call_executor_base*>(new call_executor_t<t_executor_func>(func))));
    }

    void init()
    {
      int num_threads = std::thread::hardware_concurrency();
      this->init(num_threads);
    }
    void init(size_t num_threads)
    {
      m_is_stop = false;

      for (size_t i = 0; i < num_threads; i++)
      {
        m_threads.push_back(std::thread([this]() {this->worker_func(); }));
      }
    }

    threads_pool() : m_is_stop(false), m_threads_counter(0)
    {}

    template<typename t_executor_func>
    bool add_job(t_executor_func func)
    {
      {
        std::unique_lock<std::mutex> lock(m_queue_mutex);
        m_jobs_que.push_back(build_call_executor(func));
      }
      m_condition.notify_one();
      return true;
    }

    void add_batch_and_wait(const jobs_container& cntr)
    {
      std::condition_variable batch_condition;
      std::mutex batch_mutex;


      std::atomic<size_t> cnt(0);
      for (const auto& jb : cntr)
      {
        call_executor_base* pjob = jb.get();
        add_job([&, pjob]() {
          pjob->execute();
          {
            std::lock_guard<std::mutex> lock(batch_mutex);
            cnt++;
          }
          batch_condition.notify_one();
        });
      }

      std::unique_lock<std::mutex> lock(batch_mutex);
      batch_condition.wait(lock, [&]()
      {
        return cnt == cntr.size();
      });
      //LOG_PRINT_L0("All jobs finiahed");
    }

    ~threads_pool()
    {
      m_is_stop = true;
      m_condition.notify_all();
      for (auto& th : m_threads)
      {
        th.join();
      }
    }

  private:
    void worker_func()
    {
      LOG_PRINT_L0("Worker thread is started");
      while (true)
      {
        std::shared_ptr<call_executor_base> job;
        {
          std::unique_lock<std::mutex> lock(m_queue_mutex);

          m_condition.wait(lock, [this]()
          {
            return !m_jobs_que.empty() || m_is_stop;
          });
          if (m_is_stop)
          {
            LOG_PRINT_L0("Worker thread is finished");
            return;
          }

          job = m_jobs_que.front();
          m_jobs_que.pop_front();
        }

        job->execute();
      }
    }



    jobs_container m_jobs_que;
    std::condition_variable m_condition;
    std::mutex m_queue_mutex;
    std::vector<std::thread> m_threads;
    std::atomic<bool> m_is_stop;
    std::atomic<int64_t> m_threads_counter;
  };
}