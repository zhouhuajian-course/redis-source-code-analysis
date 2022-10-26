/*
Redis 哨兵通知脚本

# NOTIFICATION SCRIPT
#
# sentinel notification-script <master-name> <script-path>
#
# Call the specified notification script for any sentinel event that is
# generated in the WARNING level (for instance -sdown, -odown, and so forth).
# This script should notify the system administrator via email, SMS, or any
# other messaging system, that there is something wrong with the monitored
# Redis systems.
#
# The script is called with just two arguments: the first is the event type
# and the second the event description.
#
# The script must exist and be executable in order for sentinel to start if
# this option is provided.
#
# Example:
#
# sentinel notification-script mymaster /var/redis/notify.sh
*/
#include <stdio.h>
// The script is called with just two arguments:
// the first is the event type
// and the second the event description.
int main(int argc, char *argv[]) {
    // argv[0]是执行的脚本名
    char *eventType = argv[1];
    char *eventDescription = argv[2];
    // a 追加 a+ 追加并可读
    fd = fopen("redis-sentinel-notification.log", "a");
    fprintf(fd, "==========\nevent type: %s\n event description: %s\n", eventType, eventDescription);
    fclose(fd);
    return 0;
};


