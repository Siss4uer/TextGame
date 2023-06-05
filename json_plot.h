#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

#define MAX_OPERATES 3

typedef struct {
    int operate[4];
    char next_node[50];
} Selection;

typedef struct {
    char command[50];
    int action;
    Selection selections[MAX_OPERATES];
} Node;

void printNode(const Node* node) {
    printf("Command: %s\n", node->command);
    printf("Action: %d\n", node->action);
    for (int i = 0; i < MAX_OPERATES; i++) {
        const Selection* selection = &(node->selections[i]);
        printf("Selection %d:\n", i + 1);
        printf("Operate: %d, %d, %d, %d\n", selection->operate[0], selection->operate[1], selection->operate[2], selection->operate[3]);
        printf("Next Node: %s\n", selection->next_node);
    }
    printf("\n");
}

void readNode(const cJSON* nodeItem, Node* node) {
    cJSON* commandItem = cJSON_GetObjectItemCaseSensitive(nodeItem, "command");
    if (commandItem != NULL && cJSON_IsString(commandItem)) {
        strncpy(node->command, commandItem->valuestring, sizeof(node->command) - 1);
        node->command[sizeof(node->command) - 1] = '\0';
    }

    cJSON* actionItem = cJSON_GetObjectItemCaseSensitive(nodeItem, "action");
    if (actionItem != NULL && cJSON_IsNumber(actionItem)) {
        node->action = actionItem->valueint;
    }

    cJSON* operateItem = cJSON_GetObjectItemCaseSensitive(nodeItem, "Operate");
    if (operateItem != NULL && cJSON_IsObject(operateItem)) {
        int i = 0;
        cJSON* selectionItem = operateItem->child;
        while (selectionItem != NULL && i < MAX_OPERATES) {
            cJSON* operateArrayItem = cJSON_GetObjectItemCaseSensitive(selectionItem, "operate");
            cJSON* nextNodeItem = cJSON_GetObjectItemCaseSensitive(selectionItem, "next_node");

            if (operateArrayItem != NULL && cJSON_IsArray(operateArrayItem) && cJSON_GetArraySize(operateArrayItem) == 4 &&
                nextNodeItem != NULL && cJSON_IsString(nextNodeItem)) {
                Selection* selection = &(node->selections[i]);

                for (int j = 0; j < 4; j++) {
                    cJSON* operateItem = cJSON_GetArrayItem(operateArrayItem, j);
                    if (operateItem != NULL && cJSON_IsNumber(operateItem)) {
                        selection->operate[j] = operateItem->valueint;
                    }
                }

                strncpy(selection->next_node, nextNodeItem->valuestring, sizeof(selection->next_node) - 1);
                selection->next_node[sizeof(selection->next_node) - 1] = '\0';

                i++;
            }

            selectionItem = selectionItem->next;
        }
    }
}

int json_plot() {
    const char* filename = "pack_01.json";

    // 读取 JSON 文件内容
    FILE* file; 
    fopen_s(&file, filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* fileContent = (char*)malloc(fileSize + 1);
    if (fileContent == NULL) {
        printf("Failed to allocate memory.\n");
        fclose(file);
        return 1;
    }

    fread(fileContent, 1, fileSize, file);
    fileContent[fileSize] = '\0';
    fclose(file);

    // 解析 JSON 文件
    cJSON* root = cJSON_Parse(fileContent);
    free(fileContent);

    if (root == NULL) {
        const char* errorPtr = cJSON_GetErrorPtr();
        if (errorPtr != NULL) {
            printf("Failed to parse JSON: %s\n", errorPtr);
        }
        else {
            printf("Failed to parse JSON.\n");
        }
        return 1;
    }

    // 遍历节点
    cJSON* nodeItem = root->child;
    while (nodeItem != NULL) {
        Node node;
        readNode(nodeItem, &node);
        printNode(&node);
        nodeItem = nodeItem->next;
    }

    cJSON_Delete(root);

    return 0;
}

#pragma once
