
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1569.85 | 0.872196 | 9589.45ms | 4219120 | 30 | 1.49927e+10 | 2.5631e+06 | 0.734667 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1183.23 | 1.23346 | 5567.45ms | 4219120 | 80 | 1.4075e+11 | 3.40059e+06 | 5.16429 | -(Loss) | false |
