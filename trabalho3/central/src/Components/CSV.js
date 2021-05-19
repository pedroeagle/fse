import { CSVLink } from "react-csv";
import "./CSV.css"

const CSV = ({ data }) => {
    // eslint-disable-next-line
    const headers = [{ key: "evento" }, { key: "dispositivo" }, { key: "horario" }];
    return (
        <div className="downloadDiv">
            {data.length > 0 ? <CSVLink className="downloadLink" data={data} filename="Logs - Central de Controle.csv">Download Logs</CSVLink> : ''}
        </div>
    );
}
export default CSV;