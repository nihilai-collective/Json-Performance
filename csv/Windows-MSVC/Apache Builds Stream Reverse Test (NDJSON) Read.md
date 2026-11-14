
----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 959.68 | 0.580575 | 7619.56ms | 4212000 | 40 | 2.36211e+10 | 4.18564e+06 | 1.12615 | 3.16664 | 1(Win) | true |
| simdjson (ondemand) | 870.034 | 0.41025 | 8254.96ms | 4212000 | 80 | 2.87006e+10 | 4.61692e+06 | 0.0385416 | 3.49303 | 2(Loss) | true |
