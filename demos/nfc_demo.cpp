/*
 * Copyright 2016 <Admobilize>
 * MATRIX Labs  [http://creator.matrix.one]
 * This file is part of MATRIX Creator HAL
 *
 * MATRIX Creator HAL is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "../cpp/driver/nfc_spi.h"
#include "../cpp/driver/wishbone_bus.h"

namespace hal = matrix_hal;

int main() {
  hal::WishboneBus bus;
  bus.SpiInit();
 
  hal::NFCSpi nfc;
  nfc.Setup(&bus);
  nfc.Reset();
  nfc.Reset(); 
  unsigned char tx[2] = {0x94,0x00}; //Read FIFO status
  unsigned char rx[2];
  nfc.Transfer((uint16_t *)tx,(uint16_t *)rx,sizeof(tx)/sizeof(uint16_t));
  std::cout << "Read Data : " << std::hex << (int)rx[0] <<" :" << (int)rx[0] << std::endl; 
  
  tx[0]= 0x12;  
  tx[1]= 0x01;
  nfc.Transfer((uint16_t *)tx,(uint16_t *)rx,sizeof(tx)/sizeof(uint16_t));
  memset(rx,0,sizeof rx);
  tx[0]= 0x94;
  tx[1]= 0x00;
  nfc.Transfer((uint16_t *)tx,(uint16_t *)rx,sizeof(tx)/sizeof(uint16_t));
  std::cout << "Read Data : " << std::hex << (int)rx[0] <<" :" << (int)rx[0] << std::endl;
  tx[0]= 0x12;
  tx[1]= 0x02;
  nfc.Transfer((uint16_t *)tx,(uint16_t *)rx,sizeof(tx)/sizeof(uint16_t));
  memset(rx,0,sizeof rx);
  tx[0]= 0x94;
  tx[1]= 0x00;
  nfc.Transfer((uint16_t *)tx,(uint16_t *)rx,sizeof(tx)/sizeof(uint16_t));
  std::cout << "Read Data : " << std::hex << (int)rx[0] <<" :" << (int)rx[0] << std::endl;

  unsigned char FIFO_tx[5] = {0x12,0x01,0x02,0x03,0x04};
  unsigned char FIFO_rx[5];
  nfc.BurstTransfer(FIFO_tx,FIFO_rx,sizeof(FIFO_tx));


 /* int length = sizeof(FIFO_tx); 
  for (int i = 1; i < length; i++) {
    data_tx[0] = FIFO_tx[0];
    data_tx[1] = FIFO_tx[i]; 
    nfc.Transfer((uint16_t *)data_tx,(uint16_t *)data_rx,sizeof(data_tx)/sizeof(uint16_t));
  }
  */
  memset(rx,0,sizeof rx);
  tx[0]= 0x94;
  tx[1]= 0x00;
  nfc.BurstTransfer(tx,rx,sizeof(tx));
  std::cout << "Read Data : " << std::hex << (int)rx[0] <<" :" << (int)rx[0] << std::endl;


  
  //tx[0] = 0x8006; 
  //nfc.Transfer((uint16_t *)tx,(uint16_t *)rx,1);
  //std::cout << "Read Data : " << std::hex  <<  rx[0]  << std::endl; 
  return 0;
}
