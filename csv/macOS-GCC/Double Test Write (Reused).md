
----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 864.936 | 1.7897 | 229.086ms | 1811 | 40 | 51084.5 | 1996.8 | 1.73913 | 1(Win) | true |
| simdjson (reflection) | 652.065 | 0.297694 | 296.986ms | 1997 | 4890 | 369677 | 2920.7 | 2.25121 | 2(Loss) | true |
| Glaze | 645.505 | 0.316502 | 284.685ms | 1798 | 4890 | 345654 | 2656.38 | 0.184889 | 3(Loss) | true |
