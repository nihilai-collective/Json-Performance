
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2988.95 | 0.0323917 | 125.96ms | 3862 | 160 | 25.4904 | 1232.24 | 0.0629333 | 0.810658 | 1(Win) | true |
| Jsonifier | 2943.4 | 0.0266221 | 129.03ms | 3862 | 320 | 35.5109 | 1251.31 | 0.133539 | 0.823096 | 2(Loss) | true |
| Glaze | 1436.83 | 0.0285197 | 265.417ms | 3862 | 160 | 85.5119 | 2563.35 | 0.0136521 | 1.70588 | 3(Loss) | true |
| simdjson (ondemand) | 820.257 | 0.0248614 | 456.152ms | 3862 | 30 | 37.3851 | 4490.17 | 0.217241 | 3.00032 | 4(Loss) | true |
