
----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 860.927 | 0.310842 | 209.06ms | 1811 | 2560 | 99545.9 | 2006.1 | 0.232214 | 2.83967 | 1(Win) | true |
| Glaze | 604.137 | 0.0303814 | 294.632ms | 1798 | 40 | 29.7429 | 2838.28 | 0.0243633 | 4.05979 | 2(Loss) | true |
