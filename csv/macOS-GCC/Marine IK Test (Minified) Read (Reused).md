
----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 663.488 | 0.876939 | 9378.13ms | 1834197 | 40 | 2.13808e+10 | 2.63641e+06 | 2.76518 | 1(Win) | true |
| Glaze | 567.598 | 0.162913 | 5313.18ms | 1834197 | 30 | 7.56209e+08 | 3.0818e+06 | 1.01195 | 2(Loss) | true |
| simdjson (reflection) | 499.205 | 1.37811 | 5687ms | 1834197 | 80 | 1.86548e+11 | 3.50402e+06 | 3.05832 | 3(Loss) | true |
| Jsonifier (two-stage) | 463.548 | 1.27604 | 5583.74ms | 1834197 | 30 | 6.95584e+10 | 3.77356e+06 | 4.32823 | 4(Loss) | true |
| simdjson (ondemand) | 399.076 | 1.06564 | 7095.25ms | 1834197 | 40 | 8.72697e+10 | 4.38319e+06 | 0.116188 | 5(Loss) | true |
