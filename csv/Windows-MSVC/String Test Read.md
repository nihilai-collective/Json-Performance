
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 502.957 | 0.232126 | 1860.19ms | 9578 | 1280 | 2.27481e+06 | 18161.2 | 0.484564 | 4.90942 | 1(Win) | true |
| simdjson (ondemand) | 442.365 | 0.652711 | 2091.16ms | 9578 | 1280 | 2.32509e+07 | 20648.8 | 0.469077 | 5.58474 | 2(Loss) | true |
