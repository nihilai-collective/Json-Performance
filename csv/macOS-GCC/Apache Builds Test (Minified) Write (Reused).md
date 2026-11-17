
----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10995.4 | 0.968475 | 839.13ms | 94653 | 320 | 2.02288e+06 | 8209.6 | 0.195274 | 1(Win) | true |
| simdjson (reflection) | 8541.32 | 0.502709 | 1104.11ms | 94653 | 640 | 1.80648e+06 | 10568.4 | 1.45534 | 2(Loss) | true |
| Glaze | 5096.93 | 0.273966 | 1745.52ms | 94653 | 4890 | 1.15121e+07 | 17710.3 | 0.300732 | 3(Loss) | true |
