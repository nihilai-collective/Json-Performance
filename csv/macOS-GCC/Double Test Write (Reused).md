
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 1125.85 | 1.10252 | 197.354ms | 1997 | 640 | 222613 | 1691.6 | 0.118371 | 1(Win) | true |
| Jsonifier | 893.706 | 1.08085 | 219.064ms | 1997 | 1280 | 679056 | 2131 | 0.476368 | 2(Loss) | true |
| Glaze | 589.489 | 1.79051 | 301.065ms | 1798 | 160 | 434011 | 2908.8 | 2.59594 | 3(Loss) | true |
