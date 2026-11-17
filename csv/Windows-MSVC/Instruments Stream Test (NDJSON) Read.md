
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1288.14 | 0.0679244 | 10205.3ms | 4197496 | 30 | 1.33669e+08 | 3.10763e+06 | 0.184941 | 1.92201 | 1(Win) | true |
| simdjson (ondemand) | 973.213 | 0.0875711 | 6692.64ms | 4197496 | 30 | 3.89231e+08 | 4.11322e+06 | 1.72128 | 2.54397 | 2(Loss) | true |
