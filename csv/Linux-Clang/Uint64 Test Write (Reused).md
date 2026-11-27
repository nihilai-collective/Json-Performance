
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2263.26 | 0.103209 | 59.1131ms | 1213 | 80 | 22.2627 | 511.125 | 0.0734214 | 1.03709 | 1(Win) | true |
| Glaze | 1107.09 | 0.238221 | 112.141ms | 1213 | 4890 | 30298.7 | 1044.91 | 0.0405488 | 2.18158 | 2(Loss) | true |
