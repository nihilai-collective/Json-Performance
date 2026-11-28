
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1913.03 | 0.0480143 | 63.8444ms | 1213 | 320 | 26.9755 | 604.7 | 0.0806835 | 1.23872 | 1(Win) | true |
| Glaze | 1024.48 | 0.0634382 | 117.804ms | 1213 | 80 | 41.0492 | 1129.16 | 0.00332094 | 2.36012 | 2(Loss) | true |
| simdjson (ondemand) | 327.309 | 0.263806 | 358.082ms | 1213 | 40 | 3477.24 | 3534.3 | 0.0745635 | 7.5095 | 3(Loss) | true |
