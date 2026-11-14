
----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13241.9 | 0.158732 | 1021.7ms | 136037 | 4890 | 1.18264e+06 | 9797.31 | 0.564162 | 1(Win) | true |
| Glaze | 4794.3 | 0.529001 | 2701.06ms | 136076 | 320 | 6.56108e+06 | 27068 | 0.0443131 | 2(Loss) | true |
| simdjson (reflection) | 346.932 | 0.226179 | 9732.64ms | 136037 | 640 | 4.57835e+08 | 373949 | 0.705465 | 3(Loss) | true |
