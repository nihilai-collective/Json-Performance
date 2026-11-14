
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 347.892 | 0.0281832 | 537.332ms | 1811 | 160 | 313.22 | 4964.48 | 0.174921 | 7.07726 | 1(Win) | true |
| simdjson (ondemand) | 290.123 | 0.0652336 | 600.299ms | 1811 | 30 | 452.414 | 5953 | 0.190018 | 8.49389 | 2(Loss) | true |
