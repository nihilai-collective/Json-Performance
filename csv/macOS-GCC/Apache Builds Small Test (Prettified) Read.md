
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) DID NOT CONVERGE | 1142.43 | 0.883271 | 274.716ms | 3370 | 640 | 395157 | 2813.2 | 7.4118 | -(Win) | false |
| simdjson (ondemand) | 886.859 | 0.285895 | 359.707ms | 3370 | 4890 | 524895 | 3623.89 | 0.196086 | 2(Loss) | true |
