
----
### Marine IK Small Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1885.3 | 0.418524 | 240.143ms | 4604 | 4890 | 464579 | 2328.92 | 0.155654 | 1(Win) | true |
| simdjson (reflection) | 1718.26 | 1.3354 | 315.727ms | 4918 | 160 | 212590 | 2729.6 | 0.117371 | 2(Loss) | true |
| Glaze | 994.117 | 0.279448 | 444.354ms | 4604 | 2560 | 389976 | 4416.7 | 1.94263 | 3(Loss) | true |
