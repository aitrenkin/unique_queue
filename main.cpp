
#include <iostream>
#include <queue>
#include <mutex>
#include <unordered_set>
#include <thread>

template <class T>
class unique_queue
{
    std::unordered_set<T> m_index;
    std::queue<T> m_container;
    std::mutex m_mutex;
    public:
      void push(const T& v)
      {
          std::lock_guard<std::mutex> lock(m_mutex);
          if(m_index.count(v) == 0)
          {
              m_index.insert(v);
              m_container.push(v);
          }
      }
      void pop()
      {
          std::lock_guard<std::mutex> lock(m_mutex);
          m_index.erase(m_container.front());
          m_container.pop();
      }
      bool empty()
      {
          std::lock_guard<std::mutex> lock(m_mutex);
          return m_container.empty();
      }
      size_t size()
      {
          std::lock_guard<std::mutex> lock(m_mutex);
          return m_container.size();
      }
      T& front()
      {
          std::lock_guard<std::mutex> lock(m_mutex);
          return  m_container.front();
      }
      T& back()
      {
          std::lock_guard<std::mutex> lock(m_mutex);
          return m_container.back();
      }

};

template <class T>
void print_queue(T &queue)
{
    while(!queue.empty())
    {
        std::cout << queue.front() << ' ';
        queue.pop();
    }
    std::cout << '\n';
}
int main()
{
    unique_queue<int> uq;
    //
    std::thread t1([&uq]{
        for(auto &i : {1,3,5,7,9,10,11,12,13,14,15,16,17,18,19,21,23,25,27})
            uq.push(i);
    });
    //

    //
    std::thread t2([&uq]{
        for(auto &i : {2,4,6,8,10,11,12,13,14,15,16,17,18,19,20,22,24,26,28})
            uq.push(i);
    });
    //
    t1.join();
    t2.join();
    print_queue<unique_queue<int>>(uq);
    return 0;
}
