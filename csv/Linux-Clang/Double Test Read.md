
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2223.07 | 0.0813947 | 80.3251ms | 1811 | 80 | 31.9899 | 776.9 | 0.228995 | 1.07189 | 1(Win) | true |
| simdjson (stage-1) | 1034.76 | 0.284503 | 170.781ms | 1811 | 2560 | 57726.4 | 1669.09 | 0.180579 | 2.35576 | 2(Loss) | true |
