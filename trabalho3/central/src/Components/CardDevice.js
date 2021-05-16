import { Button, Card, Grid, List, ListItem, ListItemSecondaryAction, ListItemText, Typography } from "@material-ui/core";
import "./CardDevice.css";
import { useEffect, useState } from 'react';
import * as mqtt from 'react-paho-mqtt';
import { withStyles } from '@material-ui/styles';
import { makeStyles } from '@material-ui/core/styles';
const useStyles = makeStyles((theme) => ({
    root: {
      flexGrow: 1,
    },
    paper: {
      padding: theme.spacing(2),
      textAlign: 'center',
      color: theme.palette.text.secondary,
    },
  }));
function CardDevice({ devices, modo, subscribe, comodoHost, client, devicesInfo, remove }) {
    const subscribeToChannels = (comodo) => {
        subscribe(client, comodoHost.toString().replace('comodo', comodo));
    }
    const classes = useStyles();
    return (
        <Grid container spacing={2} autoCorrect={true} className="grid" justify="flex-start" alignItems="flex-start">
            {devices.map((device, index) => {
                subscribeToChannels(device.comodo);
                return (
                    <Grid item md={2} key={index} className="list">
                        <Card className={modo=='energia'?'energyCard':'batteryCard'}>
                            <Typography variant="h4">{device.comodo}</Typography>
                            <Typography variant="h6">Modo: {modo}</Typography>
                            <Typography variant="h6">{device.entrada} : {devicesInfo[device.comodo]?.estado?.entrada.toString()}</Typography>
                            {modo === "energia" ?
                                <>
                                    <Typography variant="h6">{device.saida} : {devicesInfo[device.comodo]?.estado?.saida.toString()}</Typography>
                                    <Typography variant="h6" >Umidade: {devicesInfo[device.comodo]?.umidade} %</Typography>
                                    <Typography variant="h6" >Temperatura: {devicesInfo[device.comodo]?.temperatura} ºC</Typography>
                                </> : null}
                            <Typography variant="h8">MAC: {device.device}</Typography><br/>
                            <Button className="removeButton" onClick={(e)=>{remove(client, device, modo)}}>Remover dispositivo</Button>
                        </Card>
                    </Grid>
                );
            })}
        </Grid>
    );
}
export default CardDevice;