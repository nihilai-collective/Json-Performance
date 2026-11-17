
----
### Apache Builds Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20799.9 | 0.0789628 | 19.3718ms | 3643 | 1280 | 22.2664 | 167.031 | 0.367105 | 0.0998482 | 1(Win) | true |
| Glaze | 4740.48 | 0.0457392 | 77.7083ms | 3682 | 30 | 3.44368 | 740.733 | 0.166779 | 0.502761 | 2(Loss) | true |
| simdjson (reflection) | 558.213 | 0.102248 | 624.944ms | 3643 | 4890 | 198032 | 6223.86 | 0.152586 | 4.41601 | 3(Loss) | true |
