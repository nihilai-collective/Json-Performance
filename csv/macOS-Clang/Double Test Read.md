
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 912.034 | 0.0472288 | 194.802ms | 1811 | 640 | 511.928 | 1893.68 | 0.0028053 | 1(Win) | true |
| Glaze | 773.394 | 0.0506972 | 219.838ms | 1811 | 640 | 820.322 | 2233.15 | 0.00923669 | 2(Loss) | true |
| Jsonifier (two-stage) | 374.727 | 0.128084 | 467.618ms | 1811 | 2560 | 89214.7 | 4608.97 | 0.0256991 | 3(Loss) | true |
| simdjson (ondemand) | 193.777 | 0.0657671 | 877.863ms | 1811 | 160 | 5497.55 | 8912.84 | 0.262952 | 4(Loss) | true |
