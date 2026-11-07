
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12933.6 | 0.113233 | 79.1692ms | 9578 | 160 | 102.324 | 706.244 | 0.170507 | 0.18457 | 1(Win) | true |
| Glaze | 5370.68 | 0.069437 | 185.241ms | 9578 | 160 | 223.147 | 1700.77 | 0.847155 | 0.454108 | 2(Loss) | true |
