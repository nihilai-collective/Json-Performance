
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3059.58 | 0.144885 | 7930.87ms | 7351818 | 40 | 4.40931e+08 | 2.29157e+06 | 0.11448 | 0.809186 | 1(Win) | true |
| Jsonifier | 2805.92 | 0.101953 | 8487.61ms | 7351818 | 40 | 2.59596e+08 | 2.49874e+06 | 0.0845513 | 0.882338 | 2(Loss) | true |
| simdjson (ondemand) | 2472.22 | 0.108405 | 9547.76ms | 7351818 | 80 | 7.5615e+08 | 2.83601e+06 | 0.0673547 | 1.00143 | 3(Loss) | true |
| Glaze | 2330.21 | 0.0652234 | 10139.7ms | 7351818 | 80 | 3.08102e+08 | 3.00884e+06 | 0.111118 | 1.06246 | 4(Loss) | true |
