
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 867.085 | 0.0385644 | 6241ms | 1834197 | 30 | 1.81578e+07 | 2.01737e+06 | 0.16394 | 2.85526 | 1(Win) | true |
| Jsonifier (two-stage) | 792.852 | 0.0588476 | 7059ms | 1834197 | 30 | 5.05693e+07 | 2.20625e+06 | 0.166835 | 3.12261 | 2(Loss) | true |
| Glaze | 679.315 | 0.050727 | 7993.22ms | 1834197 | 160 | 2.72991e+08 | 2.57499e+06 | 0.030877 | 3.64452 | 3(Loss) | true |
| simdjson (ondemand) | 621.015 | 0.120913 | 8759.47ms | 1834197 | 80 | 9.27952e+08 | 2.81672e+06 | 0.0690063 | 3.98656 | 4(Loss) | true |
