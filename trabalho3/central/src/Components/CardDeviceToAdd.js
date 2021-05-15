import React from 'react';
import Card from '@material-ui/core/Card';
import { Button } from '@material-ui/core';

function CardDeviceToAdd({ devices, acceptDeviceFunction, denyDeviceFunction, text, modo }){
    return (
        devices.map((device, index) => {
            return(
            <Card key={index}>{text} {device}
            <Button onClick={(e)=>{acceptDeviceFunction(device, modo)}}>Adicionar</Button>
            <Button onClick={(e)=>{denyDeviceFunction(device, modo)}}>Recusar</Button>
            </Card>);
        }));
}
export default CardDeviceToAdd;