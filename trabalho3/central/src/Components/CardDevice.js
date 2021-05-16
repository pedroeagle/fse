import { Card, Grid, List, ListItem, ListItemSecondaryAction, ListItemText, Typography } from "@material-ui/core";
import "./CardDevice.css";

function CardDevice({ devices, modo }) {
    return (
            <Grid container spacing={5} autoCorrect={true} className="grid" justify="flex-start" alignItems="flex-start">
                {devices.map((device, index) => {
                    return (
                        <Grid item xs md={1} key={index} className="list">
                            <Card className="element">
                                <Typography variant="h5">{device.comodo}</Typography>
                                <Typography variant="h6">Modo: {modo}</Typography>
                                <Typography variant="h6">{device.entrada}</Typography>
                                {modo === "energia" ?
                                    <>
                                        <Typography variant="h6">{device.saida}</Typography>
                                        <Typography variant="h6">Humidade: x</Typography>
                                        <Typography variant="h6">Temperatura: y</Typography>
                                    </> : null}
                                <Typography variant="h8">MAC: {device.device}</Typography>
                            </Card>
                        </Grid>
                    );
                })}
            </Grid>
    );
}
export default CardDevice;