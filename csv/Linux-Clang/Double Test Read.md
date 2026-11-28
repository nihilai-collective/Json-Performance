
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1294.9 | 0.0870006 | 136.99ms | 1811 | 80 | 107.721 | 1333.78 | 0.0581395 | 1.87294 | 1(Win) | true |
| Glaze | 848.658 | 0.10148 | 207.366ms | 1811 | 30 | 127.955 | 2035.1 | 0.0327692 | 2.87707 | 2(Loss) | true |
| simdjson (ondemand) | 427.996 | 0.0875089 | 410.772ms | 1811 | 80 | 997.589 | 4035.32 | 0.125302 | 5.74654 | 3(Loss) | true |
