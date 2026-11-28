
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 301.252 | 0.251249 | 640.33ms | 1997 | 1280 | 322935 | 6321.91 | 0.104595 | 1(Win) | true |
| Glaze | 209.453 | 0.097935 | 824.287ms | 1798 | 40 | 2571.23 | 8186.57 | 0.196987 | 2(Loss) | true |
