/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3357 Computer Networks I
 * Western University
 * Professor Jeff Shantz
 * October 12, 2015
 * hdb.c the main class for the server side operations of storing and managing the file system
 */

#include "hdb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <hiredis/hiredis.h>

char* copy_and_malloc(const char* s) {
    // malloc for the size of the string and null character
    char* r = malloc(strlen(s) + 1);
    // copy the string to the allocated char*
    strcpy(r,s);
    // return the char* to the user
    return r;
}

void free_hdb_record(hdb_record *r){
    // free the attributes of the structre
    free(r->username);
    free(r->filename);
    free(r->checksum);
    // free the node
    free(r);
}

char *generateToken() {
    
    // set the set of characters to all letters and numbers for the alphanumeric key
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    
    // declare and initialize a string to store the token
    char *token = NULL;
    
    // declare and initialize size of token to 16-bytes
    int length = 16;
    
    srand(time(NULL));
    
    if (length) {
        token = malloc(sizeof(char) * (length + 1));
        if (token) {
            for (int i = 0; i < length; i++) {
                int key = rand() % (int)(sizeof(charset) -1);
                token[i] = charset[key];
            }
            token[length] = '\0';
        }
    }
    // return the random token
    return token;
}

void redisErrorCheck(redisReply *r) {
    // check the redis reply for errors
    if (r->type == REDIS_REPLY_ERROR) {
        fprintf(stderr, "Error: %s\n", r->str);
    }
}

hdb_connection* hdb_connect(const char* server) {
    // declare a redisContext for the connection to the server
    redisContext *c;
    // to accept port from a parameter
    int port = 6379;
    // connection times out after 1.5 seconds
    struct timeval timeout = { 1, 500000 };
    // create the new connection with specified host, port, and timeout counter
    c = redisConnectWithTimeout(server, port, timeout);
    // if the connection is NULL or there is a connection error, give an error message
    if (c == NULL || c->err) {
        if (c) {
            fprintf(stderr, "Connection Error: %s\n", c->errstr);
            // free the redisContext that was previously allocated
            redisFree(c);
        // error message if the redisContext cant be allocated
        } else {
            fprintf(stderr, "Connection Error: Can't allocate redis context\n");
        }
        // exit status for error
        exit(1);
    }
    // return the connection context cast as an hdb_connection
    return *(hdb_connection**)&c;
}

void hdb_disconnect(hdb_connection* con) {
    // disconnect from the Redis server
    redisFree((redisContext*)con);
}

void hdb_store_file(hdb_connection* con, hdb_record* record) {
    // declare and initialize a redisReply variable for the redis command HSET
    redisReply *reply = redisCommand((redisContext*)con,"HSET %s %s %s", record->username, record->filename, record->checksum);
    redisErrorCheck(reply);
    // free the redis reply object from memory
    freeReplyObject(reply);
}

int hdb_remove_file(hdb_connection* con, const char* username, const char* filename) {
    // declare and initialize a redisReply variable for the redis command HDEL
    redisReply *reply = redisCommand((redisContext*)con,"HDEL %s %s", username, filename);
    redisErrorCheck(reply);
    // create an integer variable to return the reply after freeing it
    int re = reply->integer;
    // free the redis reply object from memory
    freeReplyObject(reply);
    // return the return value of the deletion operation
    return re;
}

char* hdb_file_checksum(hdb_connection* con, const char* username, const char* filename) {
    // declare and initialize the redis reply for the HGET redis command
    redisReply* reply = redisCommand((redisContext*)con, "HGET %s %s", username, filename);
    redisErrorCheck(reply);
    // return the checksum if the redis return is not NULL
    if (reply->str != NULL) {
        char *cs = malloc(reply->len + 1);
        strcpy(cs, reply->str);
        // free the redisReply from memory
        freeReplyObject(reply);
        return cs;
    }
    // free the redisReply from memory
    freeReplyObject(reply);
    // return NULL if the file doesnt exist
    return NULL;
    
}

int hdb_file_count(hdb_connection* con, const char* username) {
    // declare and initialize a redisReply variable for the HLEN command
    redisReply *reply = redisCommand((redisContext*)con,"HLEN %s", username);
    redisErrorCheck(reply);
    // create an integer variable to return the reply after freeing it
    int f = reply->integer;
    // free the redisReply object from memory
    freeReplyObject(reply);
    // return the number of file fields the user has stored
    return f;
}

bool hdb_user_exists(hdb_connection* con, const char* username) {
    // declare and initialize a redisReply variable for the HLEN command
    redisReply *reply = redisCommand((redisContext*)con,"HLEN %s", username);
    redisErrorCheck(reply);
    // create an integer variable to return the reply after freeing it
    int f = reply->integer;
    // free the redis reply object from memory
    freeReplyObject(reply);
    // if files exist, return true
    if (f > 0) return true;
    // return false if the user does not exist
    else {
        // declare and initialize a redisReply variable for the HLEN command
        redisReply *replypass = redisCommand((redisContext*)con,"HLEN %s%s", username, "_DATA");
        redisErrorCheck(replypass);
        // create an integer variable to return the reply after freeing it
        int fpass = replypass->integer;
        // free the redis reply object from memory
        freeReplyObject(replypass);
        // if files exist, return true
        if (fpass > 0) return true;
        else return false;
    }
}

bool hdb_file_exists(hdb_connection* con, const char* username, const char* filename) {
    // declare and initialize a redisReply variable for the HEXISTS command
    redisReply *reply = redisCommand((redisContext*)con,"HEXISTS %s %s", username, filename);
    redisErrorCheck(reply);
    // create an integer variable to return the reply after freeing it
    int f = reply->integer;
    // free the redis reply object from memory
    freeReplyObject(reply);
    // if the file exists, return true
    if (f > 0) {
        return true;
    }
    // return false if the file does not exist
    else {
        return false;
    }
}

hdb_record* hdb_user_files(hdb_connection* con, const char* username) {
    // declare and initialize a redisReply variable for redis command HGETALL
    redisReply *reply = redisCommand((redisContext*)con,"HGETALL %s", username);
    redisErrorCheck(reply);
    // if the user doesnt exist with files, return NULL
    if (reply->elements == 0) {
        freeReplyObject(reply);
        return NULL;
    }
    // if the user exists with files, create a linked list of their files
    // declare temp and head nodes of the linked list
    hdb_record *temp;
    // initialize head node to NULL to be pointed to in loop
    hdb_record *head = NULL;
    // loop through the elements in the HGETALL reply
    for (int i = 0; i < reply->elements; ) {
        // allocate memory for the node in the linked list
        temp = malloc(sizeof(hdb_record));
        // set the attributes of the hdb_record for the user file
        temp->username = copy_and_malloc(username);
        temp->filename = copy_and_malloc(reply->element[i++]->str);
        temp->checksum = copy_and_malloc(reply->element[i++]->str);
        // set the temp node to point to the head of the linked list
        temp->next = head;
        // set the next node in the linked list to temp to be populated next
        head = temp;
    }
    // free the redisReply from memory
    freeReplyObject(reply);
    // return the head of the linked list
    return head;
}

void hdb_free_result(hdb_record* record) {
    // declare a temporary hdb_record
    hdb_record* n;
    // if the record is already NULL, return out of this method
    if (record == NULL) return;
    // use the helper method to free the record until it is NULL
    while (record != NULL) {
        n = record->next;
        free_hdb_record(record);
        record = n;
    }
}

char* hdb_authenticate(hdb_connection* con, const char* username, const char* password) {

    char *token;
    
    // if there exists the user already, verify the password
    if (hdb_user_exists(con, username)) {
        
        // declare and initialize a redisReply variable for the redis command HGET
        redisReply *verify = redisCommand((redisContext*)con,"HGET %s%s %s", username, "_DATA", "PASSWORD");
        redisErrorCheck(verify);
        
        if (strcmp(verify->str, password) == 0) {
            
            // generate the random token
            token = generateToken();
            
            // declare and initialize a redisReply variable for the redis command HSET
            redisReply *reply = redisCommand((redisContext*)con,"HSET %s %s %s", token, "TOKEN", username);
            redisErrorCheck(reply);
            // free the redis reply object from memory
            freeReplyObject(reply);
            //freeReplyObject(verify);
            return token;
        }
        else {
            // error message for a password that doesn't match
            fprintf(stderr, "Error: Given password for %s does not match our records\n", username);
	    //freeReplyObject(verify);
            exit(1);
        }
        
        // free the redis reply object from memory
        freeReplyObject(verify);
        
    }
    // case where the password doesn't exist
    else {
        // declare and initialize a redisReply variable for the redis command HSET
        redisReply *addUser = redisCommand((redisContext*)con,"HSET %s%s %s %s", username, "_DATA", "PASSWORD", password);
        redisErrorCheck(addUser);
        // free the redis reply object from memory
        freeReplyObject(addUser);
        
        // generate the random token
        token = generateToken();
        
        // declare and initialize a redisReply variable for the redis command HSET
        redisReply *addToken = redisCommand((redisContext*)con,"HSET %s %s %s", token, "TOKEN", username);
        redisErrorCheck(addToken);
        // free the redis reply object from memory
        freeReplyObject(addToken);
        return token;
    }
}

char* hdb_verify_token(hdb_connection* con, const char* token) {
    
    // declare and initialize a redisReply variable for the redis command HGET
    redisReply *verify = redisCommand((redisContext*)con,"EXISTS %s", token);
    redisErrorCheck(verify);
    
    // if there exists the token, get the associated username
    if (verify->integer == 1) {
        // declare and initialize a redisReply variable for the redis command HGET
        redisReply *user = redisCommand((redisContext*)con,"HGET %s %s", token, "TOKEN");
        redisErrorCheck(user);
        char *userReturn = user->str;
        freeReplyObject(user);
        // free the redis reply object from memory
        freeReplyObject(verify);
        return userReturn;
    }
    else {
        // free the redis reply object from memory
        freeReplyObject(verify);
        return NULL;
    }
}

int hdb_delete_user(hdb_connection* con, const char* username) {
    // declare and initialize a redisReply variable for redis command HDEL
    redisReply *reply = redisCommand((redisContext*)con,"DEL %s", username);
    redisErrorCheck(reply);
    // create an integer variable to return the reply after freeing it
    int f = reply->integer;
    // free the redis reply object from memory
    freeReplyObject(reply);
    // return the response from the redis deletion command
    return f;
}
