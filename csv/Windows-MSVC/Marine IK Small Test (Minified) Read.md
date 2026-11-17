
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 484.247 | 0.173183 | 918.607ms | 4604 | 4890 | 1.20575e+06 | 9067.1 | 0.257713 | 5.09465 | 1(Win) | true |
| Jsonifier (two-stage) | 451.256 | 0.29215 | 998.132ms | 4604 | 30 | 24241.4 | 9730 | 0.0342466 | 5.47465 | 2(Loss) | true |
| simdjson (ondemand) | 177.447 | 0.352487 | 2495.16ms | 4604 | 320 | 2.43426e+06 | 24743.8 | 0.00252595 | 13.9351 | 3(Loss) | true |
| Glaze | 147.92 | 0.14506 | 2984.81ms | 4604 | 2560 | 4.74624e+06 | 29683 | 0.00737007 | 16.7207 | 4(Loss) | true |
