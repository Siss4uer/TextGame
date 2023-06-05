#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "struct.h"
#include <string.h>
#define MAX_OPERATES 3
/*int item_WRITE(ITEM item) {
	FILE* fp;
	fopen_s(&fp, "itemID.json", "a+");
	// 创建一个空的JSON对象
	cJSON* itemObj = cJSON_CreateObject();
	cJSON* itemnbtArry = cJSON_CreateArray();
	cJSON* itemOperateArry = cJSON_CreateArray();
	//创建NBT数组对象
	cJSON* nbt_1 = cJSON_CreateNumber(item.NBT[0]);
	cJSON* nbt_2 = cJSON_CreateNumber(item.NBT[1]);
	cJSON* nbt_3 = cJSON_CreateNumber(item.NBT[2]);
	//NBT键值加入数组
	cJSON_AddItemToArray(itemnbtArry, nbt_1);
	cJSON_AddItemToArray(itemnbtArry, nbt_2);
	cJSON_AddItemToArray(itemnbtArry, nbt_3);
	//创建Operate数组对象
	cJSON* operate_1 = cJSON_CreateNumber(item.NBT[0]);
	cJSON* operate_2 = cJSON_CreateNumber(item.NBT[1]);
	cJSON* operate_3 = cJSON_CreateNumber(item.NBT[2]);
	cJSON* operate_4 = cJSON_CreateNumber(item.NBT[2]);
	//Operate键值加入数组
	cJSON_AddItemToArray(itemOperateArry, operate_1);
	cJSON_AddItemToArray(itemOperateArry, operate_2);
	cJSON_AddItemToArray(itemOperateArry, operate_3);
	cJSON_AddItemToArray(itemOperateArry, operate_4);
	//添加键值
	cJSON_AddNumberToObject(itemObj, "ITEMID", item.ITEMID);
	cJSON_AddStringToObject(itemObj, "ITEMNAME", item.ITEMNAME);
	cJSON_AddItemToObject(itemObj, "NBT", itemnbtArry);
	cJSON_AddItemToObject(itemObj, "OPERATE", itemOperateArry);
	// 将JSON对象转换为字符串
	char* item_json_str = cJSON_Print(itemObj);
	if (fp != NULL) {
		fputs(item_json_str, fp);
	}
	else {
		return 0;
	}
	cJSON_Delete(itemObj);
	free(item_json_str);
	fclose(fp);
	free(fp);
}*/

ITEM* getItemByID(cJSON* root, int itemID) {
    // 遍历键值对
    cJSON* currentItem = root->child;
    while (currentItem != NULL) {
        cJSON* itemIDNode = cJSON_GetObjectItem(currentItem, "ITEMID");
        if (itemIDNode != NULL && itemIDNode->valueint == itemID) {
            ITEM* item = (ITEM*)malloc(sizeof(ITEM));
            if (item == NULL) {
                printf("Failed to allocate memory for item.\n");
                return NULL;
            }

            item->ITEMID = itemID;

            cJSON* itemNameNode = cJSON_GetObjectItem(currentItem, "ITEMNAME");
            if (itemNameNode != NULL) {
                strncpy(item->ITEMNAME, itemNameNode->valuestring, sizeof(item->ITEMNAME) - 1);
                item->ITEMNAME[sizeof(item->ITEMNAME) - 1] = '\0';
            }
            else {
                printf("ITEMNAME not found for ITEMID: %d\n", itemID);
                free(item);
                return NULL;
            }

            cJSON* nbtNode = cJSON_GetObjectItem(currentItem, "NBT");
            if (nbtNode != NULL && cJSON_IsArray(nbtNode) && cJSON_GetArraySize(nbtNode) == 3) {
                for (int i = 0; i < 3; i++) {
                    cJSON* nbtItemNode = cJSON_GetArrayItem(nbtNode, i);
                    if (nbtItemNode != NULL && cJSON_IsNumber(nbtItemNode)) {
                        item->NBT[i] = nbtItemNode->valueint;
                    }
                    else {
                        printf("Invalid NBT value for ITEMID: %d\n", itemID);
                        free(item);
                        return NULL;
                    }
                }
            }
            else {
                printf("Invalid NBT array for ITEMID: %d\n", itemID);
                free(item);
                return NULL;
            }

            cJSON* operateNode = cJSON_GetObjectItem(currentItem, "OPERATE");
            if (operateNode != NULL && cJSON_IsArray(operateNode) && cJSON_GetArraySize(operateNode) == 4) {
                for (int i = 0; i < 4; i++) {
                    cJSON* operateItemNode = cJSON_GetArrayItem(operateNode, i);
                    if (operateItemNode != NULL && cJSON_IsNumber(operateItemNode)) {
                        item->OPERATE[i] = operateItemNode->valueint;
                    }
                    else {
                        printf("Invalid OPERATE value for ITEMID: %d\n", itemID);
                        free(item);
                        return NULL;
                    }
                }
            }
            else {
                printf("Invalid OPERATE array for ITEMID: %d\n", itemID);
                free(item);
                return NULL;
            }

            return item;
        }

        currentItem = currentItem->next;
    }

    printf("ITEMID not found: %d\n", itemID);
    return NULL;
}

ITEM* item_GET(int ItemID) {
    // 打开文件
    FILE* file = fopen("itemID.json", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    // 获取文件大小
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // 读取文件内容
    char* fileContent = (char*)malloc(fileSize + 1);
    if (fileContent == NULL) {
        printf("Failed to allocate memory.\n");
        fclose(file);
        return;
    }
    fread(fileContent, sizeof(char), fileSize, file);
    fileContent[fileSize] = '\0';

    // 解析JSON数据
    cJSON* root = cJSON_Parse(fileContent);
    if (root == NULL) {
        printf("Failed to parse JSON data.\n");
        free(fileContent);
        fclose(file);
        return;
    }

    // 获取ITEMID为1的项
    ITEM* item = getItemByID(root, ItemID);
    if (item != NULL) {
        return item;
        free(item);
    }

    // 释放资源
    cJSON_Delete(root);
    free(fileContent);
    fclose(file);
    return;
}


Node printNode(const Node* node) {
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

int json_plot(PLOT_STORAGE* plot_storage,char* filename) {
    // 读取 JSON 文件内容
    FILE* file;
    fopen_s(&file, filename, "r");
    if (file == NULL) {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    char* fileContent = (char*)malloc(fileSize + 1);
    if (fileContent == NULL) {
        printf("Failed to allocate memory.\n");
        fclose(file);
        return;
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
        return;
    }

    // 遍历节点
    cJSON* nodeItem = root->child;
    int order = 0;
    while (nodeItem != NULL) {
        Node node;
        readNode(nodeItem, &node);
        strcpy(plot_storage->file_node[order].command, node.command);
        plot_storage->file_node[order].action = node.action;
        plot_storage->file_node[order].selections->operate[0] = node.selections->operate[0];
        plot_storage->file_node[order].selections->operate[1] = node.selections->operate[1];
        plot_storage->file_node[order].selections->operate[2] = node.selections->operate[2];
        plot_storage->file_node[order].selections->operate[3] = node.selections->operate[3];
        strcpy(plot_storage->file_node[order].selections->next_node, node.selections->next_node);
        nodeItem = nodeItem->next;
        order++;
    }
    cJSON_Delete(root);

    return;
}

#pragma once


