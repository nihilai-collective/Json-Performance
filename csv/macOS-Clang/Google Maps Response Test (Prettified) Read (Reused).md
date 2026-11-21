
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2824.23 | 1.29625 | 885.897ms | 25388 | 40 | 493967 | 8572.92 | 0.265345 | 1(Win) | true |
| Jsonifier (two-stage) | 2460.15 | 0.031488 | 1124.51ms | 25388 | 30 | 288.102 | 9841.63 | 0.0145661 | 2(Loss) | true |
| Glaze | 1819.02 | 0.377772 | 1370.88ms | 25388 | 1280 | 3.23632e+06 | 13310.4 | 0.292731 | 3(Loss) | true |
| simdjson (ondemand) | 1718.11 | 0.0949172 | 1429.65ms | 25388 | 2560 | 458023 | 14092.2 | 0.00973682 | 4(Loss) | true |
