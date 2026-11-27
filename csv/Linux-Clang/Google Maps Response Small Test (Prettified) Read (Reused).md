
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3939.08 | 0.13977 | 246.837ms | 9378 | 30 | 302.12 | 2270.47 | 0.0132114 | 0.621561 | 1(Win) | true |
| Jsonifier (two-stage) | 3644.38 | 0.107969 | 268.241ms | 9378 | 30 | 210.616 | 2454.07 | 0.105834 | 0.671753 | 2(Loss) | true |
| Glaze | 2778.93 | 0.0372317 | 342.939ms | 9378 | 80 | 114.863 | 3218.35 | 0.0621051 | 0.883941 | 3(Loss) | true |
| simdjson (ondemand) | 2197.58 | 0.250809 | 433.882ms | 9378 | 30 | 3125.65 | 4069.73 | 0.0499374 | 1.11932 | 4(Loss) | true |
