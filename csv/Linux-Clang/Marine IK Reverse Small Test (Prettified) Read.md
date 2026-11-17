
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2471.87 | 0.430972 | 687.778ms | 18245 | 640 | 588999 | 7039.12 | 0.782654 | 0.997179 | 1(Win) | true |
| Jsonifier | 2009.4 | 0.177257 | 864.327ms | 18245 | 4890 | 1.15205e+06 | 8659.2 | 0.194122 | 1.22793 | 2(Loss) | true |
| simdjson (ondemand) | 1816.14 | 0.128708 | 967.525ms | 18245 | 40 | 6082.23 | 9580.65 | 0.197837 | 1.35928 | 3(Loss) | true |
| Glaze | 1662.19 | 0.347836 | 1060.11ms | 18245 | 320 | 424255 | 10468 | 0.0274124 | 1.48552 | 4(Loss) | true |
