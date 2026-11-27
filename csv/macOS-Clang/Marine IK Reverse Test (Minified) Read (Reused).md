
----
### Marine IK Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 783.376 | 0.437623 | 8640.21ms | 1834197 | 160 | 1.52781e+10 | 2.23293e+06 | 1.76228 | 1(Win) | true |
| Jsonifier (two-stage) | 600.378 | 0.430801 | 10056.7ms | 1834197 | 80 | 1.26034e+10 | 2.91354e+06 | 3.76157 | 2(Loss) | true |
| Glaze | 544.171 | 0.0569266 | 5383.22ms | 1834197 | 40 | 1.3394e+08 | 3.21448e+06 | 0.00120106 | 3(Loss) | true |
| simdjson (ondemand) | 432.16 | 0.577806 | 6818.53ms | 1834197 | 40 | 2.1879e+10 | 4.04763e+06 | 1.96006 | 4(Loss) | true |
