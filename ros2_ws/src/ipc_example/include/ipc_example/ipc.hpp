#ifndef ipc_example__ipc_HPP_
#define ipc_example__ipc_HPP_

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <string>

namespace ipc
{
    class IpcExample : public rclcpp::Node
    {
    public:
        IpcExample();
        ~IpcExample();

    private:
       

        void msg_timer_callback();

        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr msg_pub_;
        rclcpp::TimerBase::SharedPtr msg_timer_;
    };
} // namespace ipc
#endif // ipc_example__ipc_HPP_
