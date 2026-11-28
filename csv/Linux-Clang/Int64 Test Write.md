
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 331.839 | 0.0186796 | 374.172ms | 1313 | 160 | 79.4929 | 3773.44 | 0.11342 | 7.40735 | 1(Win) | true |
| Glaze | 282.991 | 0.15405 | 449.378ms | 1313 | 4890 | 227206 | 4424.79 | 0.35147 | 8.69584 | 2(Loss) | true |
