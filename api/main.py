from fastapi import FastAPI
from pydantic import BaseModel
from influxdb_client import InfluxDBClient, Point
from influxdb_client.client.write_api import SYNCHRONOUS
from dotenv import load_dotenv
import os

load_dotenv()

app = FastAPI()

client = InfluxDBClient(
    url=os.getenv("INFLUX_URL"),
    token=os.getenv("INFLUX_TOKEN"),
    org=os.getenv("INFLUX_ORG")
)
write_api = client.write_api(write_options=SYNCHRONOUS)

class Maaling(BaseModel):
    temperature: float
    humidity: float
    co2: int

@app.post("/maaling")
def modtag_maaling(maaling: Maaling):
    point = (
        Point("sensorpark")
        .field("temperature", maaling.temperature)
        .field("humidity", maaling.humidity)
        .field("co2", maaling.co2)
    )
    write_api.write(bucket=os.getenv("INFLUX_BUCKET"), record=point)
    return {"status": "ok"}


@app.get("/maaling")
def hent_maaling():
    query_api = client.query_api()
    query = f'''
    from(bucket: "{os.getenv("INFLUX_BUCKET")}")
      |> range(start: -1d)
      |> pivot(rowKey: ["_time"], columnKey: ["_field"], valueColumn: "_value")
    '''
    tables = query_api.query(query, org=os.getenv("INFLUX_ORG"))
    
    result = []
    for table in tables:
        for record in table.records:
            result.append({
                "time": record.get_time().isoformat(),
                "temperature": record.values.get("temperature"),
                "humidity": record.values.get("humidity"),
                "co2": record.values.get("co2")
            })
    
    return result


