#include "ros.h"

states state;

rcl_publisher_t publisher;
std_msgs__msg__Bool msg;
std_msgs__msg__Bool received_msg_drop;
std_msgs__msg__Bool received_msg_grab;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_subscription_t subscriber_drop;
rcl_subscription_t subscriber_grab;
rclc_executor_t executor;

void init_ros() {
  Serial.printf("Connecting to ap: %s\n", ENV_WIFI_SSID);
  IPAddress agent_ip(ENV_AGENT_IP);
  uint16_t agent_port = 8888;
  set_microros_wifi_transports(ENV_WIFI_SSID, ENV_WIFI_PASSWORD, agent_ip, agent_port);
  state = states::WAITING_AGENT;
}

void ZdcHandshakeCallback(const void* msgin) {
  const std_msgs__msg__Bool* msg = (const std_msgs__msg__Bool*)msgin;
  Serial.print("pince en bas...");
}

void GrabHandshakeCallback(const void* msgin) {
  const std_msgs__msg__Bool* msg = (const std_msgs__msg__Bool*)msgin;
  if (msg->data) {
    update_grabber(GRABBER_POS_CLOSED);
  } else {
    update_grabber(GRABBER_POS_OPEN);
  }
}

bool create_entities() {
  allocator = rcl_get_default_allocator();
  
  rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
  RCCHECK(rcl_init_options_init(&init_options, allocator));
  RCCHECK(rcl_init_options_set_domain_id(&init_options, 42));
  RCCHECK(rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator));
  RCCHECK(rclc_node_init_default(&node, "actionneurs", "", &support));

  RCCHECK(rclc_publisher_init_best_effort(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
    "/temp"));

  RCCHECK(rclc_executor_init(&executor, &support.context, 2, &allocator));
  RCCHECK(rclc_subscription_init_default(&subscriber_drop, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
    "/drop"));
  RCCHECK(rclc_subscription_init_default(&subscriber_grab, &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Bool),
    "/grab"));

  RCCHECK(rclc_executor_add_subscription(&executor, &subscriber_drop, &received_msg_drop,
      &ZdcHandshakeCallback, ON_NEW_DATA));
  RCCHECK(rclc_executor_add_subscription(&executor, &subscriber_grab, &received_msg_grab,
      &GrabHandshakeCallback, ON_NEW_DATA));

  Serial.println("ROS initialized");
  
  return true;
}

void destroy_entities() {
  rmw_context_t * rmw_context = rcl_context_get_rmw_context(&support.context);
  (void) rmw_uros_set_context_entity_destroy_session_timeout(rmw_context, 0);

  (void) rcl_publisher_fini(&publisher, &node);
  (void) rclc_executor_fini(&executor);
  (void) rcl_subscription_fini(&subscriber_drop, &node);
  (void) rcl_subscription_fini(&subscriber_grab, &node);
  (void) rcl_node_fini(&node);
  rclc_support_fini(&support);
}

void ros_loop() {
  switch (state) {
  case states::WAITING_AGENT:
    EXECUTE_EVERY_N_MS(500, state = (RMW_RET_OK == rmw_uros_ping_agent(100, 1))
                                        ? states::AGENT_AVAILABLE
                                        : states::WAITING_AGENT;);
    break;
  case states::AGENT_AVAILABLE:
    state = (true == create_entities()) ? states::AGENT_CONNECTED : states::WAITING_AGENT;
    if (state == states::WAITING_AGENT) {
      destroy_entities();
    };
    break;
  case states::AGENT_CONNECTED:
    EXECUTE_EVERY_N_MS(200, state = (RMW_RET_OK == rmw_uros_ping_agent(100, 1))
                                        ? states::AGENT_CONNECTED
                                        : states::AGENT_DISCONNECTED;);
    if (state == states::AGENT_CONNECTED) {
        // EXECUTE_EVERY_N_MS(100, ros_update_obstacle());
        // EXECUTE_EVERY_N_MS(100, ros_update_odometry());
        // EXECUTE_EVERY_N_MS(1000, ros_update_batt());
        rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));
    }
    break;
  case states::AGENT_DISCONNECTED:
    destroy_entities();
    state = states::WAITING_AGENT;
    break;
  default:
    break;
  }
}