
----
### Twitter Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Twitter%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1496.33 | 0.988382 | 9903.47ms | 4219120 | 40 | 2.82554e+10 | 2.68903e+06 | 0.589478 | 1(Win) | true |
| simdjson (ondemand) | 1183.92 | 1.66993 | 5922.19ms | 4219120 | 30 | 9.66312e+10 | 3.3986e+06 | 0.665464 | 2(Loss) | true |
