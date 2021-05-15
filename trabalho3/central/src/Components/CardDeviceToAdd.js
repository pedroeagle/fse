import React from 'react';
import Card from '@material-ui/core/Card';
import { Button } from '@material-ui/core';

function CardDeviceToAdd({ devices, acceptDeviceFunction, denyDeviceFunction }){
    return (
        devices.map((device, index) => {
            return(
            <Card key={index}>{device}
            <Button onClick={(e)=>{acceptDeviceFunction(device)}}>Adicionar</Button>
            <Button onClick={(e)=>{denyDeviceFunction(device)}}>Recusar</Button>
            </Card>);
        }));
}
export default CardDeviceToAdd;