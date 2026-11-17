
----
### String Test Read Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 813.066 | 0.0866473 | 1168.2ms | 9578 | 1280 | 121288 | 11234.4 | 1.61871 | 3.73036 | 1(Win) | true |
| simdjson (ondemand) | 781.063 | 0.660422 | 1227.89ms | 9578 | 320 | 1.90884e+06 | 11694.7 | 0.173389 | 3.88326 | 2(Loss) | true |
