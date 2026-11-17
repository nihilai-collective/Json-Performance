
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1359.92 | 0.67005 | 131.541ms | 1811 | 30 | 2172.41 | 1270 | 0 | 1.77348 | 1(Win) | true |
| simdjson (stage-1) | 282.091 | 0.0767361 | 624.111ms | 1811 | 80 | 1765.82 | 6122.5 | 0 | 8.71524 | 2(Loss) | true |
