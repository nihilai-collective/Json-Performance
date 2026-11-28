
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 327.414 | 0.0725263 | 388.554ms | 1313 | 30 | 230.806 | 3824.43 | 0.252525 | 7.50881 | 1(Win) | true |
| Glaze | 286.14 | 0.181034 | 456.141ms | 1313 | 2560 | 160670 | 4376.08 | 0.128366 | 8.60115 | 2(Loss) | true |
