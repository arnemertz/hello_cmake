#ifndef BOUNDED_QUEUE_HPP_
#define BOUNDED_QUEUE_HPP_

#include <queue>
#include <condition_variable>
#include <mutex>

template <typename T>
class BoundedQueue {
public:
	explicit BoundedQueue(int capacity)
    :mCapacity(capacity) 
    {}

	void Enqueue(const T element) {
        std::unique_lock<std::mutex> lock(mQueueMutex);
        mOverflowCondition.wait(lock, [this]{ return mQueue.size() < mCapacity; });
        mQueue.push(element);
        mUnderflowCondition.notify_one();
    }

	T Dequeue() {
        std::unique_lock<std::mutex> lock(mQueueMutex);
        mUnderflowCondition.wait(lock, [this]{ return mQueue.size() > 0; });
        T element = mQueue.front();
        mQueue.pop();
        mOverflowCondition.notify_one();        
        return element; 
    }
	
    //! Anzahl Elemente in Queue
    int Size() const {
        std::unique_lock<std::mutex> lock(mQueueMutex);
        return mQueue.size();
    } 
	
    //! Max. Anzahl Elemente
    int Capacity() const {
        return mCapacity;
    } 

private:
    std::queue<T> mQueue{};
    const std::size_t mCapacity = 0;
    std::condition_variable_any mOverflowCondition;
    std::condition_variable_any mUnderflowCondition;
    mutable std::mutex mQueueMutex;
};


#endif
