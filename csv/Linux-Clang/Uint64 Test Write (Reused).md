
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2275.19 | 0.0785079 | 59.7656ms | 1213 | 160 | 25.4937 | 508.444 | 0.0873524 | 1.03305 | 1(Win) | true |
| Glaze | 1118.23 | 0.143134 | 111.697ms | 1213 | 30 | 65.7759 | 1034.5 | 0.119363 | 2.1576 | 2(Loss) | true |
