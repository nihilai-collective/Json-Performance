
----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 9338.97 | 2.36919 | 29.7032ms | 2632 | 4890 | 198281 | 268.774 | 0.711554 | 1(Win) | true |
| simdjson (reflection) | 6000.79 | 1.7464 | 43.275ms | 2632 | 4890 | 260948 | 418.29 | 1.33004 | 2(Loss) | true |
| Glaze | 2873.62 | 0.617142 | 90.9719ms | 2632 | 4890 | 142100 | 873.489 | 0.694776 | 3(Loss) | true |
