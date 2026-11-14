
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1497.17 | 0.127079 | 746.912ms | 11579 | 160 | 14056.2 | 7375.62 | 0.413502 | 2.02649 | 1(Win) | true |
| Jsonifier | 1420.7 | 0.0559071 | 782.26ms | 11579 | 4890 | 92337.7 | 7772.64 | 0.505258 | 2.13364 | 2(Loss) | true |
| simdjson (ondemand) | 858.657 | 0.153829 | 1292.36ms | 11579 | 640 | 250473 | 12860.3 | 0.116774 | 3.53186 | 3(Loss) | true |
| Glaze | 777.573 | 0.0543187 | 1426.48ms | 11579 | 2560 | 152335 | 14201.4 | 0.137068 | 3.90314 | 4(Loss) | true |
