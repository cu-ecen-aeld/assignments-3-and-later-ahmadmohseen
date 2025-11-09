/**
 * @file writer.c
 * @brief A utility to write a string to a file with syslog logging
 * 
 * This program writes a specified string to a file and logs the operation
 * using syslog. It is an alternative to the writer.sh script.
 * 
 * Usage: writer <file> <string>
 *   <file>   - Path to the file to write
 *   <string> - String to write to the file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    // Open syslog with LOG_USER facility
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);
    
    // Check if both arguments are provided
    if (argc != 3) {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        fprintf(stderr, "Usage: %s <file> <string>\n", argv[0]);
        syslog(LOG_ERR, "Invalid number of arguments: %d", argc - 1);
        closelog();
        return 1;
    }
    
    const char *writefile = argv[1];
    const char *writestr = argv[2];
    
    // Log the write operation with LOG_DEBUG level
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);
    
    // Open the file for writing (create if doesn't exist, truncate if exists)
    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        fprintf(stderr, "Error: Could not open file %s: %s\n", writefile, strerror(errno));
        syslog(LOG_ERR, "Could not open file %s: %s", writefile, strerror(errno));
        closelog();
        return 1;
    }
    
    // Write the string to the file
    size_t len = strlen(writestr);
    ssize_t bytes_written = write(fd, writestr, len);
    
    if (bytes_written == -1) {
        fprintf(stderr, "Error: Could not write to file %s: %s\n", writefile, strerror(errno));
        syslog(LOG_ERR, "Could not write to file %s: %s", writefile, strerror(errno));
        close(fd);
        closelog();
        return 1;
    }
    
    if ((size_t)bytes_written != len) {
        fprintf(stderr, "Error: Partial write to file %s\n", writefile);
        syslog(LOG_ERR, "Partial write to file %s: wrote %zd of %zu bytes", 
               writefile, bytes_written, len);
        close(fd);
        closelog();
        return 1;
    }
    
    // Close the file
    if (close(fd) == -1) {
        fprintf(stderr, "Error: Could not close file %s: %s\n", writefile, strerror(errno));
        syslog(LOG_ERR, "Could not close file %s: %s", writefile, strerror(errno));
        closelog();
        return 1;
    }
    
    // Close syslog
    closelog();
    
    return 0;
}

