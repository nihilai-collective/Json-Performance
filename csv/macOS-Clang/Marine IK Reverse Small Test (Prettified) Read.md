
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1483.46 | 2.16379 | 1084.92ms | 18245 | 40 | 2.57649e+06 | 11729.2 | 0.188064 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1435.19 | 0.33005 | 1086.86ms | 18245 | 2560 | 4.09894e+06 | 12123.7 | 0.0113852 | 1(Tie) | true |
| Glaze | 1134.81 | 0.734356 | 1602.9ms | 18245 | 160 | 2.0285e+06 | 15332.8 | 2.65863 | 3(Loss) | true |
| simdjson (ondemand) | 1081.22 | 0.766923 | 1605.71ms | 18245 | 640 | 9.74861e+06 | 16092.7 | 1.51401 | 4(Loss) | true |
