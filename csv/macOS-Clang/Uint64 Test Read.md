
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1036.4 | 0.195681 | 117.287ms | 1213 | 80 | 381.64 | 1116.17 | 0.418344 | 1(Win) | true |
| Glaze | 651.974 | 0.244857 | 177.504ms | 1213 | 2560 | 48319.7 | 1774.31 | 0.077643 | 2(Loss) | true |
| simdjson (ondemand) | 276.182 | 0.0942729 | 427.915ms | 1213 | 40 | 623.687 | 4188.57 | 0.0583275 | 3(Loss) | true |
