
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2408.79 | 0.0930803 | 8559.18ms | 360584 | 1280 | 2.26017e+07 | 142760 | 0.0655214 | 1(Win) | true |
| simdjson (ondemand) | 1940.86 | 0.133404 | 5105.01ms | 360584 | 160 | 8.93894e+06 | 177179 | 0.0261813 | 2(Loss) | true |
