
----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 791.052 | 0.820006 | 233.735ms | 1811 | 2560 | 820542 | 2183.3 | 3.79395 | 1(Win) | true |
| simdjson (reflection) | 669.275 | 0.562442 | 321.167ms | 1997 | 1280 | 327879 | 2845.6 | 1.91977 | 2(Loss) | true |
| Glaze | 576.932 | 0.351844 | 316.555ms | 1798 | 4890 | 534737 | 2972.11 | 2.70361 | 3(Loss) | true |
