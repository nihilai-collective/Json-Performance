
----
### Apache Builds Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 8526.81 | 2.22339 | 32.32ms | 2632 | 4890 | 209478 | 294.374 | 0.77844 | 1(Win) | true |
| simdjson (reflection) DID NOT CONVERGE | 6728.36 | 1.95587 | 38.986ms | 2632 | 4890 | 260342 | 373.058 | 6.40573 | -(Loss) | false |
| Glaze | 2808 | 0.844747 | 87.7819ms | 2632 | 2560 | 145973 | 893.9 | 1.97353 | 3(Loss) | true |
