import { CSVLink } from "react-csv";
import "./CSV.css"

const CSV = ({ data }) => {
    const headers = [{ key: "evento" }, { key: "dispositivo" }, { key: "horario" }];
    return (
        <div className="downloadDiv">
            {data.length > 0 ? <CSVLink className="downloadLink" data={data}>Download Logs</CSVLink> : ''}
        </div>
    );
}
export default CSV;