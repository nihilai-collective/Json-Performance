
----
### Instruments Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21656.3 | 0.24287 | 953.22ms | 213963 | 1280 | 670297 | 9422.24 | 0.275131 | 0.11401 | 1(Win) | true |
| Glaze | 4460.49 | 0.0942357 | 4631.96ms | 213963 | 1280 | 2.37877e+06 | 45746.3 | 0.0141527 | 0.554742 | 2(Loss) | true |
