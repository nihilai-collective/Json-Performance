
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2356.83 | 0.0780207 | 160.648ms | 3873 | 320 | 478.42 | 1567.18 | 0.11731 | 1(Win) | true |
| Glaze | 1308.42 | 0.140228 | 277.124ms | 3873 | 80 | 1253.6 | 2822.94 | 0.108604 | 2(Loss) | true |
| Jsonifier (two-stage) | 844.74 | 0.0921503 | 442.92ms | 3873 | 2560 | 41560.7 | 4372.45 | 0.0402751 | 3(Loss) | true |
| simdjson (ondemand) | 472.477 | 0.143949 | 788.47ms | 3873 | 1280 | 162091 | 7817.49 | 0.0039873 | 4(Loss) | true |
