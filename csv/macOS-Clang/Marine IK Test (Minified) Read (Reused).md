
----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 675.364 | 0.822509 | 9199.83ms | 1834197 | 30 | 1.3615e+10 | 2.59005e+06 | 0.559352 | 1(Win) | true |
| Jsonifier (two-stage) | 608.411 | 0.460649 | 10233.5ms | 1834197 | 40 | 7.01614e+09 | 2.87508e+06 | 1.06531 | 2(Loss) | true |
| Glaze | 492.462 | 0.61065 | 6031.03ms | 1834197 | 80 | 3.76376e+10 | 3.55201e+06 | 1.29946 | 3(Loss) | true |
| simdjson (ondemand) | 416.156 | 0.579332 | 6982.43ms | 1834197 | 40 | 2.37189e+10 | 4.2033e+06 | 0.193641 | 4(Loss) | true |
