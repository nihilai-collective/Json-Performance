
----
### Twitter Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1672.95 | 0.220646 | 8585.25ms | 4219120 | 40 | 1.12649e+09 | 2.40513e+06 | 0.522797 | 1(Win) | true |
| simdjson (ondemand) | 1382.95 | 0.256344 | 10169.3ms | 4219120 | 160 | 8.90012e+09 | 2.90947e+06 | 1.75364 | 2(Loss) | true |
