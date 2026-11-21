
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 941.84 | 0.0553136 | 405.232ms | 3862 | 80 | 374.303 | 3910.53 | 0.0671716 | 2.61133 | 1(Win) | true |
| Glaze | 788.637 | 0.231635 | 459.926ms | 3862 | 2560 | 299583 | 4670.2 | 0.397401 | 3.12133 | 2(Loss) | true |
