
----
### Marine IK Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2155.05 | 0.268864 | 221.955ms | 4918 | 4890 | 167432 | 2176.37 | 0.0674266 | 1(Win) | true |
| simdjson (reflection) | 2119.66 | 0.384657 | 225.314ms | 4918 | 2560 | 185452 | 2212.7 | 0.193956 | 2(Loss) | true |
| Glaze | 1165.48 | 0.2837 | 382.812ms | 4604 | 2560 | 292429 | 3767.3 | 0.461333 | 3(Loss) | true |
