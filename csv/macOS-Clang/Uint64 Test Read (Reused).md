
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2426.72 | 0.408512 | 152.201ms | 3873 | 1280 | 49485.3 | 1522.05 | 0.578986 | 1(Win) | true |
| Glaze | 1210.19 | 1.59198 | 284.612ms | 3873 | 80 | 188867 | 3052.07 | 0.813266 | 2(Loss) | true |
| Jsonifier (two-stage) | 841.54 | 0.123133 | 468.76ms | 3873 | 80 | 2336.6 | 4389.07 | 1.06897 | 3(Loss) | true |
| simdjson (ondemand) | 444.959 | 0.279736 | 847.378ms | 3873 | 2560 | 1.38035e+06 | 8300.94 | 0.846219 | 4(Loss) | true |
