
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1464.68 | 0.203054 | 88.8264ms | 1313 | 160 | 482.156 | 854.913 | 0.153289 | 1(Win) | true |
| Glaze | 778.058 | 0.313513 | 165.759ms | 1313 | 640 | 16292.8 | 1609.36 | 0.00961083 | 2(Loss) | true |
| simdjson (ondemand) | 288.309 | 0.320217 | 436.886ms | 1313 | 1280 | 247578 | 4343.16 | 0.673007 | 3(Loss) | true |
