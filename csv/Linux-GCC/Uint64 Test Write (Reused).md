
----
### Uint64 Test Write (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4732.78 | 0.117589 | 87.5ms | 3873 | 40 | 33.6865 | 780.425 | 0.00106778 | 0.505945 | 1(Win) | true |
| simdjson (reflection) | 3188.66 | 0.0531573 | 122.253ms | 3873 | 80 | 30.3316 | 1158.35 | 0.00863371 | 0.758737 | 2(Loss) | true |
| Glaze | 1846.79 | 0.0425481 | 212.28ms | 3873 | 30 | 21.7241 | 2000 | 0.0667111 | 1.32313 | 3(Loss) | true |
