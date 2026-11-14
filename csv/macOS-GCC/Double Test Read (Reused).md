
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Glaze | 1000.76 | 0.790001 | 191.254ms | 1811 | 1280 | 237928 | 1725.8 | 0.31388 | 1(Win) | true |
| Jsonifier | 902.636 | 1.5953 | 170.639ms | 1811 | 2560 | 2.38527e+06 | 1913.4 | 0.146123 | 2(Loss) | true |
| Jsonifier (two-stage) | 441.015 | 0.594568 | 375.464ms | 1811 | 1280 | 693974 | 3916.2 | 0.51848 | 3(Loss) | true |
| simdjson (ondemand) | 135.014 | 0.304889 | 1288.72ms | 1811 | 2560 | 3.89404e+06 | 12792 | 3.15694 | 4(Loss) | true |
