
----
### Canada Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 890.75 | 0.061465 | 9228.71ms | 2251027 | 80 | 1.75548e+08 | 2.41004e+06 | 0.0146767 | 1(Win) | true |
| Jsonifier (two-stage) | 774.104 | 0.0568437 | 10428.5ms | 2251027 | 80 | 1.988e+08 | 2.7732e+06 | 0.0530052 | 2(Loss) | true |
| Glaze | 703.076 | 0.0723455 | 5435.83ms | 2251027 | 30 | 1.46387e+08 | 3.05336e+06 | 4.64909 | 3(Loss) | true |
| simdjson (ondemand) | 619.402 | 0.0772719 | 6027.74ms | 2251027 | 30 | 2.15169e+08 | 3.46583e+06 | 0.00825803 | 4(Loss) | true |
