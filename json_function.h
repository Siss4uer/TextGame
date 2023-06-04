#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "struct.h"
#include <string.h>
int item_WRITE(ITEM item) {
	FILE* fp;
	fopen_s(&fp, "itemID.json", "a+");
	// ����һ���յ�JSON����
	cJSON* itemObj = cJSON_CreateObject();
	cJSON* itemnbtArry = cJSON_CreateArray();
	cJSON* itemOperateArry = cJSON_CreateArray();
	//����NBT�������
	cJSON* nbt_1 = cJSON_CreateNumber(item.NBT[0]);
	cJSON* nbt_2 = cJSON_CreateNumber(item.NBT[1]);
	cJSON* nbt_3 = cJSON_CreateNumber(item.NBT[2]);
	//NBT��ֵ��������
	cJSON_AddItemToArray(itemnbtArry, nbt_1);
	cJSON_AddItemToArray(itemnbtArry, nbt_2);
	cJSON_AddItemToArray(itemnbtArry, nbt_3);
	//����Operate�������
	cJSON* operate_1 = cJSON_CreateNumber(item.NBT[0]);
	cJSON* operate_2 = cJSON_CreateNumber(item.NBT[1]);
	cJSON* operate_3 = cJSON_CreateNumber(item.NBT[2]);
	cJSON* operate_4 = cJSON_CreateNumber(item.NBT[2]);
	//Operate��ֵ��������
	cJSON_AddItemToArray(itemOperateArry, operate_1);
	cJSON_AddItemToArray(itemOperateArry, operate_2);
	cJSON_AddItemToArray(itemOperateArry, operate_3);
	cJSON_AddItemToArray(itemOperateArry, operate_4);
	//��Ӽ�ֵ
	cJSON_AddNumberToObject(itemObj, "ITEMID", item.ITEMID);
	cJSON_AddStringToObject(itemObj, "ITEMNAME", item.ITEMNAME);
	cJSON_AddItemToObject(itemObj, "NBT", itemnbtArry);
	cJSON_AddItemToObject(itemObj, "OPERATE", itemOperateArry);
	// ��JSON����ת��Ϊ�ַ���
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
}

ITEM* getItemByID(cJSON* root, int itemID) {
    // ������ֵ��
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
    // ���ļ�
    FILE* file = fopen("itemID.json", "r");
    if (file == NULL) {
        printf("Failed to open file.\n");
        return;
    }

    // ��ȡ�ļ���С
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // ��ȡ�ļ�����
    char* fileContent = (char*)malloc(fileSize + 1);
    if (fileContent == NULL) {
        printf("Failed to allocate memory.\n");
        fclose(file);
        return;
    }
    fread(fileContent, sizeof(char), fileSize, file);
    fileContent[fileSize] = '\0';

    // ����JSON����
    cJSON* root = cJSON_Parse(fileContent);
    if (root == NULL) {
        printf("Failed to parse JSON data.\n");
        free(fileContent);
        fclose(file);
        return;
    }

    // ��ȡITEMIDΪ1����
    ITEM* item = getItemByID(root, ItemID);
    if (item != NULL) {
        return item;
        free(item);
    }

    // �ͷ���Դ
    cJSON_Delete(root);
    free(fileContent);
    fclose(file);
    return;
}

#pragma once

