import React from 'react';
import Card from '@material-ui/core/Card';
import { Button } from '@material-ui/core';

function CardDeviceToAdd({ devices, acceptDeviceFunction, denyDeviceFunction }){
    return (
        devices.map((device, index) => {
            return(
            <Card key={index} value={device} >{device}
            <Button value={device} onClick={acceptDeviceFunction}>Adicionar</Button>
            <Button value={device} onClick={denyDeviceFunction}>Recusar</Button>
            </Card>);
        }));
}
export default CardDeviceToAdd;