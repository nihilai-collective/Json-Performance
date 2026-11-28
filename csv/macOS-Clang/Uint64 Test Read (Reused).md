
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1390.51 | 0.180765 | 87.1642ms | 1213 | 2560 | 5789.49 | 831.93 | 0.290407 | 1(Win) | true |
| Glaze | 730.789 | 0.147625 | 163.184ms | 1213 | 4890 | 26703.4 | 1582.96 | 0.330502 | 2(Loss) | true |
| simdjson (ondemand) | 258.826 | 0.202719 | 455.717ms | 1213 | 4890 | 401424 | 4469.45 | 0.550037 | 3(Loss) | true |
