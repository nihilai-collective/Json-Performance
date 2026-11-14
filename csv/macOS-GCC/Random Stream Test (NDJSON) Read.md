
----
### Random Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 964.718 | 0.707892 | 7822.08ms | 4506447 | 80 | 7.95593e+10 | 4.45486e+06 | 2.32884 | 1(Win) | true |
| simdjson (ondemand) | 603.838 | 1.5907 | 5464.29ms | 4506447 | 30 | 3.84528e+11 | 7.11728e+06 | 1.95798 | 2(Loss) | true |
