
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2650.85 | 0.145854 | 55.1835ms | 1313 | 30 | 14.2402 | 472.367 | 0.0564852 | 0.884996 | 1(Win) | true |
| simdjson (reflection) | 2407.56 | 0.0421629 | 57.5329ms | 1313 | 320 | 15.3881 | 520.1 | 0.00240344 | 0.976642 | 2(Loss) | true |
| Glaze | 1374.91 | 0.046157 | 100.936ms | 1313 | 160 | 28.2732 | 910.731 | 0.0666117 | 1.74999 | 3(Loss) | true |
