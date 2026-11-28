
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1542.66 | 0.0980638 | 84.6869ms | 1313 | 40 | 25.3436 | 811.7 | 0.0164291 | 1.55286 | 1(Win) | true |
| Glaze | 921.496 | 0.0548657 | 138.552ms | 1313 | 40 | 22.2333 | 1358.85 | 0.0355819 | 2.63163 | 2(Loss) | true |
| simdjson (ondemand) | 351.179 | 0.0265379 | 366.652ms | 1313 | 80 | 71.6297 | 3565.62 | 0.0574604 | 6.99351 | 3(Loss) | true |
