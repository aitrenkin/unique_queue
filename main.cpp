
#include <iostream>
#include <queue>
#include <mutex>
#include <unordered_set>
#include <thread>
#include <deque>
#include <algorithm>
template <class T>
class unique_queue_s
{
    std::deque<T> m_container;
    std::mutex m_mutex;
    public:

      unique_queue_s() = default;
      unique_queue_s(const std::initializer_list<T> l)
      {
          for(const auto &i: l)
              push(i);
      }
      //
      void push(const T& v)
      {
          std::lock_guard<std::mutex> lock(m_mutex);
          if(m_container.end() ==
                  std::find(m_container.begin(),m_container.end(),v))
            m_container.push_back(v);
      }
      void pop()
      {
          std::lock_guard<std::mutex> lock(m_mutex);
          m_container.pop_front();
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
      template< class... Args >
      void emplace( Args&&... args )
      {
          std::lock_guard<std::mutex> lock(m_mutex);
          return m_container.emplace(args...);
      }

};
template <class T>
class unique_queue
{
    std::unordered_set<T> m_index;
    std::queue<T> m_container;
    std::mutex m_mutex;
    public:

      unique_queue() = default;
      unique_queue(const std::initializer_list<T> l)
      {
          for(const auto &i: l)
              push(i);
      }
      //
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
      template< class... Args >
      void emplace( Args&&... args )
      {
          std::lock_guard<std::mutex> lock(m_mutex);
          return m_container.emplace(args...);
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
#if 0
    //******//
    unique_queue<int> uq;

    //на выходе должны получить последовательность 1..28 без повторений
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
    print_queue(uq);

    //****// // должна быть выведена последовательность 1..15 без повторов и пропусков
    unique_queue<int> uq2({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});

    std::thread t3([&uq2]{
        print_queue(uq2);
    });

    std::thread t4([&uq2]{
        print_queue(uq2);
    });
    t3.join();
    t4.join();
#endif

    //******//
    unique_queue_s<int> uq;

    //на выходе должны получить последовательность 1..28 без повторений
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
    print_queue(uq);

    //****// // должна быть выведена последовательность 1..15 без повторов и пропусков
    unique_queue_s<int> uq2({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});

    std::thread t3([&uq2]{
        print_queue(uq2);
    });

    std::thread t4([&uq2]{
        print_queue(uq2);
    });
    t3.join();
    t4.join();
    return 0;
}
