
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 309.964 | 0.140883 | 377.823ms | 1213 | 4890 | 135185 | 3732.07 | 0.0585121 | 7.9301 | 1(Win) | true |
| Glaze | 244.633 | 0.180808 | 500.334ms | 1213 | 2560 | 187140 | 4728.74 | 0.671226 | 10.063 | 2(Loss) | true |
