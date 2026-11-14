
----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1930.61 | 0.302048 | 231.183ms | 4604 | 4890 | 230750 | 2274.26 | 0.196679 | 1(Win) | true |
| simdjson (reflection) | 1621.65 | 0.187522 | 296.06ms | 4918 | 4890 | 143840 | 2892.22 | 0.590358 | 2(Loss) | true |
| Glaze | 1080.96 | 1.11984 | 447.854ms | 4604 | 30 | 62070.9 | 4061.87 | 0.833333 | 3(Loss) | true |
