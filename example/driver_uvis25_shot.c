/**
 * Copyright (C) LibDriver 2015-2021 All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_uvis25_shot.c
 * @brief     driver uvis25 shot source file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-24
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/24  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/12/06  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_uvis25_shot.h"

static uvis25_handle_t gs_handle;        /**< uvis25 handle */

/**
 * @brief     shot example init
 * @param[in] interface is the chip interface
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t uvis25_shot_init(uvis25_interface_t interface)
{
    volatile uint8_t res;
    
    /* link functions */
    DRIVER_UVIS25_LINK_INIT(&gs_handle, uvis25_handle_t);
    DRIVER_UVIS25_LINK_IIC_INIT(&gs_handle, uvis25_interface_iic_init);
    DRIVER_UVIS25_LINK_IIC_DEINIT(&gs_handle, uvis25_interface_iic_deinit);
    DRIVER_UVIS25_LINK_IIC_READ(&gs_handle, uvis25_interface_iic_read);
    DRIVER_UVIS25_LINK_IIC_WRITE(&gs_handle, uvis25_interface_iic_write);
    DRIVER_UVIS25_LINK_SPI_INIT(&gs_handle, uvis25_interface_spi_init);
    DRIVER_UVIS25_LINK_SPI_DEINIT(&gs_handle, uvis25_interface_spi_deinit);
    DRIVER_UVIS25_LINK_SPI_READ(&gs_handle, uvis25_interface_spi_read);
    DRIVER_UVIS25_LINK_SPI_WRITE(&gs_handle, uvis25_interface_spi_write);
    DRIVER_UVIS25_LINK_DELAY_MS(&gs_handle, uvis25_interface_delay_ms);
    DRIVER_UVIS25_LINK_DEBUG_PRINT(&gs_handle, uvis25_interface_debug_print);
    DRIVER_UVIS25_LINK_RECEIVE_CALLBACK(&gs_handle, uvis25_interface_receive_callback);
    
    /* set interface */
    res = uvis25_set_interface(&gs_handle, interface);
    if (res)
    {
        uvis25_interface_debug_print("uvis25: set interface failed.\n");
       
        return 1;
    }
    
    /* uvis25 init */
    res = uvis25_init(&gs_handle);
    if (res)
    {
        uvis25_interface_debug_print("uvis25: init failed.\n");
       
        return 1;
    }
    
    /* set default iic */
    res = uvis25_set_iic(&gs_handle, UVIS25_SHOT_DEFAULT_IIC);
    if (res)
    {
        uvis25_interface_debug_print("uvis25: set iic failed.\n");
        uvis25_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default spi wire */
    res = uvis25_set_spi_wire(&gs_handle, UVIS25_SHOT_DEFAULT_SPI_WIRE);
    if (res)
    {
        uvis25_interface_debug_print("uvis25: set spi wire failed.\n");
        uvis25_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default boot */
    res = uvis25_set_boot(&gs_handle, UVIS25_SHOT_DEFAULT_BOOT_MODE);
    if (res)
    {
        uvis25_interface_debug_print("uvis25: set boot failed.\n");
        uvis25_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default block data update */
    res = uvis25_set_block_data_update(&gs_handle, UVIS25_SHOT_DEFAULT_BLOCK_DATA_UPDATE);
    if (res)
    {
        uvis25_interface_debug_print("uvis25: set block data update failed.\n");
        uvis25_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default interrupt */
    res = uvis25_set_interrupt(&gs_handle, UVIS25_BOOL_FALSE);
    if (res)
    {
        uvis25_interface_debug_print("uvis25: set interrupt failed.\n");
        uvis25_deinit(&gs_handle);
        
        return 1;
    }
    
    return 0;
}

/**
 * @brief      shot example read
 * @param[out] *uv points to a uv index buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t uvis25_shot_read(float *uv)
{
    volatile uint8_t raw;
    
    /* single read */
    if (uvis25_single_read(&gs_handle, (uint8_t *)&raw, uv))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  basic shot deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t uvis25_shot_deinit(void)
{
    /* close uvis25 */
    if (uvis25_deinit(&gs_handle))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}