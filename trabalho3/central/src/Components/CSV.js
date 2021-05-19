import { CSVLink } from "react-csv";
import "./CSV.css"

const CSV = ({ data }) => {
    const headers = [{ key: "evento" }, { key: "dispositivo" }, { key: "horario" }];
    return (
        <div className="downloadDiv">
            {data.length > 0 ? <CSVLink headers={headers} className="downloadLink" data={data} filename="Logs - Central de Controle.csv">Download Logs</CSVLink> : ''}
        </div>
    );
}
export default CSV;