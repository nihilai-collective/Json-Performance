
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 315.793 | 0.0423139 | 615.019ms | 1997 | 80 | 520.964 | 6030.81 | 0.0938047 | 1(Win) | true |
| Glaze | 226.269 | 0.0539605 | 771.612ms | 1798 | 80 | 1337.73 | 7578.16 | 0.0150125 | 2(Loss) | true |
