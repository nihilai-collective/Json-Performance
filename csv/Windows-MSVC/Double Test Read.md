
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 329.541 | 0.414083 | 549.09ms | 1811 | 640 | 301420 | 5240.94 | 0.397909 | 7.47297 | 1(Win) | true |
| simdjson (ondemand) | 132.956 | 0.100067 | 1326.21ms | 1811 | 30 | 5068.97 | 12990 | 0.205708 | 18.5761 | 2(Loss) | true |
