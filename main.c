#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DataDiri {
  char nama[255];
  char alamat[255];
  int isSet;
  struct DataDiri *next;
} DataDiri;

int validateHashTableSize(int size) {
  return size > 0? 1 : 0;
}

int cariHashValueDariNama(char *nama, int ukuranHashTable) {
  int hashValue = 0;
  for (int i = 0; i < sizeof(nama)/sizeof(nama[0]); i++) {
    hashValue += nama[i];
  }
  return hashValue % ukuranHashTable;
}

DataDiri *buatDataDiri(char *nama, char *alamat) {
  DataDiri *dataDiriBaru = (DataDiri*) malloc(sizeof(DataDiri));
  strcpy(dataDiriBaru->nama, nama);
  strcpy(dataDiriBaru->alamat, alamat);
  dataDiriBaru->next = NULL;
  dataDiriBaru->isSet = 1;
  return dataDiriBaru;
}


int upsertHashTable(DataDiri **hashTable, int ukuranHashTable) {
  char buffer[255], buffer2[255];
  printf("masukkan nama: ");

  fflush(stdin);
  fgets(buffer, 255, stdin);

  printf("masukkan alamat: ");
  fgets(buffer2, 255, stdin);

  int hashValue = cariHashValueDariNama(buffer, ukuranHashTable);
  printf("%d\n", hashValue);
  
  if ((*hashTable)[hashValue].isSet == 0) {
    (*hashTable)[hashValue].isSet = 1;
    (*hashTable)[hashValue].next = NULL;
    strcpy((*hashTable)[hashValue].nama, buffer);
    strcpy((*hashTable)[hashValue].alamat, buffer2);
  } else {
    DataDiri *dataDiriBaru = buatDataDiri(buffer, buffer2);
    DataDiri *iterator;
    iterator = &(*hashTable)[hashValue];
    while (iterator->next != NULL) {
      iterator = iterator->next;
    }
    iterator->next = dataDiriBaru;
  }
  return 1;
}

void printSeluruhIsiHashTable(DataDiri *hashTable, int ukuranHashTable) {
  DataDiri *iterator;
  for (int i = 0; i < ukuranHashTable; i++) {
    if (hashTable[i].isSet == 1) {
      printf("hash-table index ke-%d\n", i);
      iterator = &hashTable[i];
      while (iterator != NULL) {
        printf("nama: %salamat: %s", iterator->nama, iterator->alamat);
        iterator = iterator->next;
      }
      printf("\n-------------------\n");
    }
  }
}

DataDiri *cariBerdasarkanNama(DataDiri *hashTable, int ukuranHashTable) {
  char cariNama[255];
  fflush(stdin);
  printf("masukkan nama: ");
  fgets(cariNama, 255, stdin);

  int hashValue = cariHashValueDariNama(cariNama, ukuranHashTable);

  DataDiri *iterator = NULL;

  if (hashTable[hashValue].isSet == 1) {
      iterator = &hashTable[hashValue];
      while (iterator != NULL) {
        if (strcmp(iterator->nama, cariNama) == 0) {
          break;
        }
        iterator = iterator->next;
      }
  }

  return iterator;
}

int main() {
  int ukuranHashTable;
  printf("masukkan ukuran hash table: "); scanf("%d", &ukuranHashTable);

  if (!validateHashTableSize(ukuranHashTable)) {
    printf("ukuran hash table harus lebih dari 0");
    return 1;
  }

  int pil;
  DataDiri *hashTable, *dataYangDicari;
  hashTable = (DataDiri*) malloc(sizeof(DataDiri) * ukuranHashTable);

  for (int i = 0; i < ukuranHashTable; i++) {
    hashTable[i].isSet = 0;
    hashTable[i].next = NULL;
  }

  do {
    printf("menu:\n1. upsert\n2. print seluruh hash table\n3. cari berdasarkan nama\n4. keluar\npilihan: "); scanf("%d", &pil);
    switch(pil) {
      case 1:
        if (!upsertHashTable(&hashTable, ukuranHashTable)) {
          printf("gagal dalam melakukan upsert hash-table\n");
        }
        break;
      case 2:
        printSeluruhIsiHashTable(hashTable, ukuranHashTable);
        break;
      case 3:
        dataYangDicari = cariBerdasarkanNama(hashTable, ukuranHashTable);
        if (dataYangDicari == NULL) {
          printf("data tidak ditemukan\n");
        } else {
          printf("data ditemukan\nnama: %salamat:%s", dataYangDicari->nama, dataYangDicari->alamat);
        }
        break;
      case 4:
        printf("program selesai\n");
        break;
      default:
        printf("pilihan tidak valid\n");
    }
  } while (pil != 4);

  return 0;
}