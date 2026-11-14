
----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 733.012 | 0.16803 | 8427.53ms | 4197496 | 40 | 3.36816e+09 | 5.46109e+06 | 0.348952 | 4.14599 | 1(Win) | true |
| simdjson (ondemand) | 553.983 | 0.144233 | 5172.25ms | 4197496 | 40 | 4.34484e+09 | 7.22593e+06 | 0.0824448 | 5.48609 | 2(Loss) | true |
