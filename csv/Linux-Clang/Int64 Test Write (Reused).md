
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2353.49 | 0.0848425 | 61.4937ms | 1313 | 80 | 16.3013 | 532.05 | 0.00939673 | 1.00015 | 1(Win) | true |
| Glaze | 1121.32 | 0.0780659 | 121.092ms | 1313 | 160 | 121.595 | 1116.7 | 0.0917041 | 2.15598 | 2(Loss) | true |
