
----
### Google Maps Response Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10632.2 | 0.545233 | 105.993ms | 11812 | 2560 | 85429.1 | 1059.5 | 0.348006 | 1(Win) | true |
| simdjson (reflection) | 8159.23 | 0.51962 | 141.66ms | 11812 | 4890 | 251669 | 1380.62 | 0.888726 | 2(Loss) | true |
| Glaze | 1865.36 | 0.173795 | 614.649ms | 11812 | 4890 | 538648 | 6038.93 | 0.993897 | 3(Loss) | true |
