
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1234.08 | 0.10712 | 5211.24ms | 4197496 | 80 | 9.65884e+08 | 3.24376e+06 | 5.30572 | 2.00616 | -(Win) | false |
| simdjson (ondemand) DID NOT CONVERGE | 913.989 | 0.0834493 | 7050.32ms | 4197496 | 30 | 4.00743e+08 | 4.37975e+06 | 4.04355 | 2.7088 | -(Loss) | false |
