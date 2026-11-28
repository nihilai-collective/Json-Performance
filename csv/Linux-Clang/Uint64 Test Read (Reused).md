
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1820.99 | 0.0932015 | 67.0044ms | 1213 | 80 | 28.0441 | 635.263 | 0.159637 | 1.30258 | 1(Win) | true |
| Glaze | 972.788 | 0.107592 | 121.918ms | 1213 | 30 | 49.1092 | 1189.17 | 0.0196177 | 2.48634 | 2(Loss) | true |
| simdjson (ondemand) | 309.026 | 0.136923 | 380.624ms | 1213 | 40 | 1050.86 | 3743.4 | 0.255795 | 7.95418 | 3(Loss) | true |
