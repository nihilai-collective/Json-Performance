
----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9933.14 | 1.95859 | 38.1192ms | 3643 | 4890 | 229477 | 349.762 | 3.32702 | 1(Win) | true |
| Glaze | 4567.42 | 1.55888 | 85.5619ms | 3682 | 1280 | 183849 | 768.8 | 1.18252 | 2(Loss) | true |
| simdjson (reflection) | 307.346 | 0.998877 | 1109.3ms | 3643 | 160 | 2.0399e+06 | 11304 | 0.0424809 | 3(Loss) | true |
