
----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4209.08 | 0.0343318 | 96.3506ms | 3862 | 320 | 28.8797 | 875.034 | 0.0667385 | 0.571091 | 1(Win) | true |
| Glaze | 2581.91 | 0.109881 | 156.829ms | 3862 | 30 | 73.7069 | 1426.5 | 0.30705 | 0.942008 | 2(Loss) | true |
