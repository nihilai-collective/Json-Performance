
----
### Apache Builds Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1304.02 | 0.421952 | 5662.23ms | 4212000 | 80 | 1.35154e+10 | 3.08039e+06 | 2.23723 | 1(Win) | true |
| simdjson (ondemand) | 1083.88 | 0.173056 | 6769.29ms | 4212000 | 80 | 3.2906e+09 | 3.70601e+06 | 0.115021 | 2(Loss) | true |
