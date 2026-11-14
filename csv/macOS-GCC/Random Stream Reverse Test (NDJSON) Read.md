
----
### Random Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Random%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 610.834 | 0.714297 | 5398.36ms | 4506447 | 40 | 1.01028e+11 | 7.03576e+06 | 1.52346 | 1(Win) | true |
| simdjson (ondemand) | 346.713 | 0.54627 | 8878.53ms | 4506447 | 30 | 1.37552e+11 | 1.23955e+07 | 0.569981 | 2(Loss) | true |
