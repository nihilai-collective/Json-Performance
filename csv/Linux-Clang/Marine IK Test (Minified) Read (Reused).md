
----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 904.107 | 0.123464 | 6786.33ms | 1834197 | 160 | 9.12965e+08 | 1.93476e+06 | 0.206946 | 2.73833 | 1(Win) | true |
| Jsonifier (two-stage) | 809.209 | 0.649634 | 7524.38ms | 1834197 | 80 | 1.5776e+10 | 2.16165e+06 | 0.202256 | 3.05945 | 2(Loss) | true |
| Glaze | 754.176 | 0.116688 | 8305.54ms | 1834197 | 40 | 2.92997e+08 | 2.31939e+06 | 1.1748 | 3.28272 | 3(Loss) | true |
| simdjson (ondemand) | 638.508 | 0.203546 | 9444.01ms | 1834197 | 30 | 9.3284e+08 | 2.73955e+06 | 0.950291 | 3.87722 | 4(Loss) | true |
