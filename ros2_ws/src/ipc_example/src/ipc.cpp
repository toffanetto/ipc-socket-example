#include "ipc_example/ipc.hpp"

namespace ipc
{
    IpcExample::IpcExample() : Node("ipc_example")
    {
        msg_pub_ = this->create_publisher<std_msgs::msg::String>("/icp_msg", 1);
        msg_timer_ = this->create_wall_timer(std::chrono::seconds(1),
                                             std::bind(&IpcExample::msg_timer_callback, this));
    }

    IpcExample::~IpcExample()
    {
    }

    void IpcExample::msg_timer_callback()
    {

        std_msgs::msg::String msg;
        msg.data = std::string(shm_buf->string);
        RCLCPP_INFO(this->get_logger(), "Publishing IPC message | %d", shm_buf->size);
        RCLCPP_INFO(this->get_logger(), shm_buf->string);
        msg_pub_->publish(msg);
    }

} // namespace ipc
