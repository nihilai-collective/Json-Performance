
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1881.57 | 0.10235 | 1109.86ms | 18245 | 40 | 3583.33 | 9247.5 | 0.0811688 | 1.31094 | 1(Win) | true |
| Jsonifier | 1586.49 | 0.201588 | 1263.59ms | 18245 | 2560 | 1.25137e+06 | 10967.5 | 0.0719973 | 1.55642 | 2(Loss) | true |
| Glaze | 598.119 | 0.20235 | 3113.77ms | 18245 | 1280 | 4.43537e+06 | 29090.9 | 0.788918 | 4.13545 | 3(Loss) | true |
| simdjson (ondemand) | 392.398 | 0.322854 | 4623.24ms | 18245 | 320 | 6.55837e+06 | 44342.2 | 0.00916086 | 6.30516 | 4(Loss) | true |
