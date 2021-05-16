import React from 'react';
import Card from '@material-ui/core/Card';
import { Button } from '@material-ui/core';
import './CardDeviceToAdd.css';

function CardDeviceToAdd({ devices, acceptDeviceFunction, denyDeviceFunction, text, modo }){
    return (
        devices.map((device, index) => {
            return(
            <Card className="cardNewDeviceFound" key={index}>{text} {device}
            <br/>
            <Button className="acceptButton" onClick={(e)=>{acceptDeviceFunction(device, modo)}}>Adicionar</Button>
            <Button className="denyButton" onClick={(e)=>{denyDeviceFunction(device, modo)}}>Recusar</Button>
            </Card>);
        }));
}
export default CardDeviceToAdd;