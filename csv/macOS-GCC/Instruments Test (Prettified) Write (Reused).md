
----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 20989.9 | 0.131325 | 978.328ms | 213963 | 2560 | 417246 | 9721.4 | 0.0698999 | 1(Win) | true |
| Glaze | 2677.24 | 0.0589188 | 7772.2ms | 213963 | 2560 | 5.16239e+06 | 76217 | 0.0849482 | 2(Loss) | true |
| simdjson (reflection) | 320.843 | 0.301585 | 7668.11ms | 213963 | 80 | 2.94307e+08 | 635984 | 1.53827 | 3(Loss) | true |
