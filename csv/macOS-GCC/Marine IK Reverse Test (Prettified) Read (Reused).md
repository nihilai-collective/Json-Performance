
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 2163.07 | 0.285674 | 5450.62ms | 7351818 | 30 | 2.57223e+09 | 3.24134e+06 | 0.19229 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 2127.71 | 0.81781 | 5512.16ms | 7351818 | 40 | 2.90488e+10 | 3.2952e+06 | 2.10048 | 1(Tie) | true |
| Jsonifier (two-stage) | 2087.9 | 0.260353 | 5517.71ms | 7351818 | 80 | 6.11487e+09 | 3.35804e+06 | 0.0131488 | 3(Loss) | true |
| simdjson (ondemand) | 1790.79 | 0.0621705 | 6485.1ms | 7351818 | 40 | 2.36988e+08 | 3.91516e+06 | 0.14359 | 4(Loss) | true |
| Glaze | 1729.14 | 0.0712441 | 6732.15ms | 7351818 | 30 | 2.50352e+08 | 4.05477e+06 | 0.123688 | 5(Loss) | true |
