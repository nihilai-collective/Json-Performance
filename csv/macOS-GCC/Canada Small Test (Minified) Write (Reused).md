
----
### Canada Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2098.83 | 0.79274 | 209.652ms | 4630 | 1280 | 356025 | 2103.8 | 3.30024 | 1(Win) | true |
| Glaze | 1933.74 | 0.565742 | 233.468ms | 4630 | 1280 | 213605 | 2283.4 | 0.253364 | 2(Loss) | true |
| simdjson (reflection) | 913.598 | 0.206301 | 491.596ms | 4630 | 2560 | 254505 | 4833.1 | 0.134309 | 3(Loss) | true |
