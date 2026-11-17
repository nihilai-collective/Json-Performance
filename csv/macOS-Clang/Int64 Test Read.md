
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2258.73 | 0.401025 | 181.016ms | 3862 | 30 | 1282.8 | 1630.6 | 0.336165 | 1(Win) | true |
| simdjson (stage-1) | 1205.77 | 0.257662 | 307.981ms | 3862 | 4890 | 302908 | 3054.57 | 0.446286 | 2(Loss) | true |
