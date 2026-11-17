
----
### Marine IK Reverse Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1525.81 | 0.0842445 | 287.314ms | 4604 | 30 | 176.309 | 2877.63 | 0.149652 | 1.60829 | 1(Win) | true |
| simdjson (reflection) | 1324.41 | 0.0321345 | 396.929ms | 4918 | 30 | 38.8506 | 3541.33 | 0.139113 | 1.85474 | 2(Loss) | true |
| Glaze | 1076.98 | 0.0599359 | 417.079ms | 4604 | 40 | 238.83 | 4076.88 | 0.124638 | 2.28234 | 3(Loss) | true |
