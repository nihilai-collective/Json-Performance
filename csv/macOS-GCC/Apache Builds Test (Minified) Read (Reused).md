
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1602.25 | 0.229314 | 8338.55ms | 94653 | 320 | 5.34095e+06 | 56338.4 | 0.449307 | 1(Win) | true |
| simdjson (ondemand) | 893.286 | 1.17683 | 6163.98ms | 94653 | 30 | 4.24263e+07 | 101052 | 0.21156 | 2(Loss) | true |
