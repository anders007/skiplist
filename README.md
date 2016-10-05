# skiplist

这是方便我理解skiplist的项目，参考的redis的实现
考虑的应用场景为游戏中的排行榜，并没有像redis一样去节省前向指针，由于redis是all-in-memory所以节省指针的几个字节很重要


有需要的请参考redis的zset的实现
http://redis.io/

或者levelDB的实现
