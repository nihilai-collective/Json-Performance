
----
### Google Maps Response Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 876.364 | 0.159781 | 7032.52ms | 4203059 | 80 | 4.27269e+09 | 4.57384e+06 | 0.029205 | 1(Win) | true |
| simdjson (ondemand) | 810.479 | 0.134614 | 7624.07ms | 4203059 | 40 | 1.77291e+09 | 4.94565e+06 | 0.405572 | 2(Loss) | true |
