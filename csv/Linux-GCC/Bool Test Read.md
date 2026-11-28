
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2840.61 | 0.0877865 | 33.2123ms | 905 | 320 | 22.7656 | 303.834 | 0.0215943 | 0.797959 | 1(Win) | true |
| Glaze | 2376.09 | 0.225437 | 39.7045ms | 905 | 30 | 20.1161 | 363.233 | 0 | 0.970976 | 2(Loss) | true |
| simdjson (reflection) | 1247.24 | 0.0330026 | 72.4202ms | 905 | 320 | 16.6895 | 691.987 | 0.0189635 | 1.91203 | 3(Loss) | true |
| simdjson (ondemand) | 497.627 | 0.176306 | 176.651ms | 905 | 4890 | 45722.7 | 1734.38 | 0.119254 | 4.90101 | 4(Loss) | true |
