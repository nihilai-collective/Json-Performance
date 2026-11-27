
----
### Random Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 964.106 | 0.230331 | 7764.88ms | 4506446 | 30 | 3.16261e+09 | 4.45769e+06 | 1.22191 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 585.826 | 0.405327 | 5898.64ms | 4506446 | 40 | 3.53672e+10 | 7.3361e+06 | 12.655 | -(Loss) | false |
