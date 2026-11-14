
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1967.71 | 0.0932995 | 7877.83ms | 264040 | 640 | 9.12337e+06 | 127970 | 0.102316 | 1(Win) | true |
| simdjson (ondemand) | 1510.92 | 0.244016 | 5123.81ms | 264040 | 80 | 1.32308e+07 | 166659 | 0.0594873 | 2(Loss) | true |
