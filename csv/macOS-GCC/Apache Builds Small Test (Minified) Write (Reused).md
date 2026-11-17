
----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10372.2 | 7.02413 | 30.475ms | 2632 | 640 | 184925 | 242 | 2.10356 | 1(Win) | true |
| simdjson (reflection) | 6172.28 | 1.75965 | 44.044ms | 2632 | 4890 | 250404 | 406.668 | 1.54015 | 2(Loss) | true |
| Glaze | 2830.48 | 3.34447 | 88.085ms | 2632 | 640 | 562971 | 886.8 | 4.84979 | 3(Loss) | true |
