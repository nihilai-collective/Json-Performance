
----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10386.4 | 3.02465 | 36.61ms | 3643 | 2560 | 262049 | 334.5 | 0.505651 | 1(Win) | true |
| Glaze | 3672.46 | 0.535469 | 97.3949ms | 3682 | 4890 | 128184 | 956.152 | 0.488928 | 2(Loss) | true |
| simdjson (reflection) | 345.036 | 0.172017 | 1033.4ms | 3643 | 640 | 192004 | 10069.2 | 0.0833532 | 3(Loss) | true |
