
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2224.56 | 0.128054 | 41.3255ms | 905 | 80 | 19.7462 | 387.975 | 0.0322082 | 1.04124 | 1(Win) | true |
| Glaze | 207.692 | 0.192727 | 418.31ms | 905 | 2560 | 164202 | 4155.55 | 0.127326 | 11.8475 | 2(Loss) | true |
