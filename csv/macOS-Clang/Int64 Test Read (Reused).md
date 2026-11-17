
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2559.66 | 0.33237 | 147.923ms | 3862 | 30 | 686.162 | 1438.9 | 0.197298 | 1(Win) | true |
| Glaze | 1389.07 | 0.277575 | 274.403ms | 3862 | 640 | 34667.3 | 2651.49 | 0.0805621 | 2(Loss) | true |
| Jsonifier (two-stage) | 827.078 | 0.847217 | 445.191ms | 3862 | 160 | 227741 | 4453.14 | 1.27011 | 3(Loss) | true |
| simdjson (ondemand) | 437.651 | 0.231446 | 854.038ms | 3862 | 2560 | 971201 | 8415.58 | 1.67628 | 4(Loss) | true |
