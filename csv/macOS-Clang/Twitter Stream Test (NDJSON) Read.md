
----
### Twitter Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1659.87 | 0.106119 | 8396.98ms | 4219120 | 160 | 1.05876e+09 | 2.42409e+06 | 0.146662 | 1(Win) | true |
| simdjson (ondemand) | 1417.36 | 0.24251 | 9741.61ms | 4219120 | 160 | 7.58343e+09 | 2.83885e+06 | 1.40288 | 2(Loss) | true |
