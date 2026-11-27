
----
### Marine IK Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 617.736 | 0.235596 | 9333.49ms | 1834197 | 80 | 3.56051e+09 | 2.83167e+06 | 1.78887 | 1(Win) | true |
| simdjson (reflection) | 562.21 | 0.15051 | 9410.24ms | 1834197 | 80 | 1.75434e+09 | 3.11134e+06 | 3.03009 | 2(Loss) | true |
| Glaze | 536.03 | 0.0558131 | 10440.7ms | 1834197 | 30 | 9.95195e+07 | 3.2633e+06 | 1.25389 | 3(Loss) | true |
| Jsonifier (two-stage) | 475.32 | 0.789019 | 5734.15ms | 1834197 | 40 | 3.37252e+10 | 3.6801e+06 | 2.92555 | 4(Loss) | true |
| simdjson (ondemand) | 390.898 | 0.923312 | 6139.35ms | 1834197 | 30 | 5.12133e+10 | 4.47489e+06 | 0.612924 | 5(Loss) | true |
