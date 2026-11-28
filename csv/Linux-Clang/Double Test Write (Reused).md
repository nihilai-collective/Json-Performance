
----
### Double Test Write (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 896.736 | 0.0245318 | 225.244ms | 1997 | 160 | 43.4314 | 2123.8 | 0.243075 | 2.72599 | 1(Win) | true |
| Glaze | 537.655 | 0.0941588 | 329.12ms | 1798 | 30 | 270.53 | 3189.23 | 0.0355489 | 4.56704 | 2(Loss) | true |
