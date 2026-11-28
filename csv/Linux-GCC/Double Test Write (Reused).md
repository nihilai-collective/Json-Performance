
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 935.567 | 0.0528427 | 214.28ms | 1997 | 40 | 46.2846 | 2035.65 | 0.0695444 | 2.61296 | 1(Win) | true |
| simdjson (reflection) | 742.297 | 0.0421337 | 259.783ms | 1997 | 30 | 35.0575 | 2565.67 | 0.104045 | 3.30085 | 2(Loss) | true |
| Glaze | 584.172 | 0.0604561 | 311.961ms | 1798 | 80 | 251.923 | 2935.28 | 0.0281143 | 4.20104 | 3(Loss) | true |
