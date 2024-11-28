#ifndef HEADER_QT_NOTIFY
#define HEADER_QT_NOTIFY

//当时实现这个是因条件有限，使用信号与槽很麻烦，就实现了这个代替
class Notify
{
public:
	virtual void NotifyThis() {};
};

#endif
