/*
 * sharedlib.c
 *
 *  Created on: Mar 21, 2016
 *      Author: sumanth
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <semaphore.h>

typedef struct sem {
	sem_t mutex;
	int size;
	int init_flag;
	int rwflag;
	sem_t wsignal;
	sem_t rsignal;
} info_t;
info_t *info;
char *addr;

void memsh_init() {

	int mutexfd = shm_open("/critical_region.txt", O_RDWR | O_CREAT, 0666);
	ftruncate(mutexfd, sizeof(info_t));
	if ((info = mmap(NULL, sizeof(info_t), PROT_READ | PROT_WRITE,
	MAP_SHARED, mutexfd, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}
	if (info->init_flag != 1) {
		info->rwflag = 0;
		if (sem_init(&info->mutex, 1, 1) < 0) {
			perror("semaphore initialization");
			exit(1);
		}
		if (sem_init(&info->wsignal, 1, 0) < 0) {
			perror("semaphore initialization");
			exit(1);
		}
		if (sem_init(&info->rsignal, 1, 0) < 0) {
			perror("semaphore initialization");
			exit(1);
		}
		info->init_flag = 1;
	}
}

size_t memsh_write(char *msg) {
	sem_wait(&info->mutex);
	while (info->rwflag != 0) {
		sem_post(&info->mutex);
		sem_wait(&info->wsignal);
		sem_wait(&info->mutex);
	}
	int memsh_fd = shm_open("/shared_region.txt", O_RDWR | O_CREAT, 0666);
	info->size = strlen(msg);
	ftruncate(memsh_fd, info->size);
	addr = mmap(0, info->size, PROT_READ | PROT_WRITE, MAP_SHARED, memsh_fd, 0);
	strcpy(addr, msg);
	info->rwflag = 1;
	sem_post(&info->rsignal);
	sem_post(&info->mutex);
	close(memsh_fd);
	munmap(addr, info->size);

	return strlen(msg);
}
size_t memsh_read(char *msg) {

	sem_wait(&info->mutex);
	printf("Waiting for writer to write some data\n");
	while (info->rwflag == 0) {

		sem_post(&info->mutex);
		sem_wait(&info->rsignal);
		sem_wait(&info->mutex);
	}
	int memsh_fd = shm_open("/shared_region.txt", O_RDWR | O_CREAT, 0666);
	ftruncate(memsh_fd, info->size);
	addr = mmap(0, info->size, PROT_READ | PROT_WRITE, MAP_SHARED, memsh_fd, 0);
	msg = realloc(msg, info->size);
	strcpy(msg, addr);
	info->rwflag = 0;
	sem_post(&info->mutex);
	sem_post(&info->wsignal);
	close(memsh_fd);
	munmap(addr, info->size);
	return strlen(msg);
}
