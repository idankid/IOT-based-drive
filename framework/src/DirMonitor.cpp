/***********************************************
*     __	@author Idan Kideckel
* ___( o)>	@date 2025-03-22
* \ <_. )	@Ex 
*  `---' 	@reviewer Liad		 	 				
************************************************/

#include <poll.h>   /* poll */
#include <cstring> /* memcpy */
#include <sys/inotify.h> /* inotify_init */

#include "DirMonitor.hpp"

/*------------------------ inotify ---------------------------- */

int ilrd::DirMonitor::InitNotify()
{
    int fd = inotify_init();
    if(fd == -1)
    {
        throw std::runtime_error("failed to open inotify instance");
    }

    return fd;
}

int ilrd::DirMonitor::InitWatcher()
{
    int watcher = inotify_add_watch(m_notify_fd, m_path.c_str(), IN_CLOSE_WRITE | IN_DELETE);
    if(watcher == -1)
    {
        close(m_notify_fd);
        throw std::runtime_error("failed to create a watcher");
    }

    return watcher;
}

/*------------------------ DirMoniter Ctor Dtor ------------------------- */
ilrd::DirMonitor::DirMonitor(const std::string& path) : m_stop_thread(false),
 m_path(path), m_notify_fd(InitNotify()), m_watcher(InitWatcher())
{}

ilrd::DirMonitor::~DirMonitor()
{
    try
    {
        m_stop_thread = true;
        inotify_rm_watch(m_notify_fd, m_watcher);
        m_thread.join();
        close(m_notify_fd);
    }
    catch(...)
    {}
}

/*------------------------ DirMoniter register Run ------------------------- */
void ilrd::DirMonitor::Register(ACallback<const std::string&>* call)
{
    m_dispatch.Register(call);
}

void ilrd::DirMonitor::UnRegister(ACallback<const std::string&>* call)
{
    m_dispatch.Unregister(call);
}

void ilrd::DirMonitor::Run()
{
    m_thread = std::thread(&ilrd::DirMonitor::ThreadJob, this);
}


/*------------------------ DirMoniter ThreadJob ------------------------- */
void ilrd::DirMonitor::ThreadJob()
{
    while(!m_stop_thread)
    {
        char buffer[BUFSIZ] = {0};
        size_t len = read(m_notify_fd, &buffer ,BUFSIZ);
        size_t i = 0;
        while (i < len)
        {   
            inotify_event* event = reinterpret_cast<inotify_event*>(&buffer[i]);
            try
            {
                if(event->mask & IN_DELETE)
                {
                    m_dispatch.Notify(static_cast<std::string>("-") + m_path + '/' + event->name);
                }
                if(event->mask & IN_CLOSE_WRITE)
                {
                    m_dispatch.Notify(static_cast<std::string>("+") + m_path + '/' + event->name);
                }

            }
            catch(const std::exception& e)
            {}
            
            i += sizeof(inotify_event) + event->len;
        }
    }
}