
----
### Github Events Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1092.21 | 0.476662 | 5434.6ms | 53331 | 80 | 3.94145e+06 | 46566.4 | 0.0274801 | 1(Win) | true |
| simdjson (ondemand) | 462.778 | 0.2225 | 5829.12ms | 53331 | 160 | 9.56743e+06 | 109902 | 0.00436732 | 2(Loss) | true |
