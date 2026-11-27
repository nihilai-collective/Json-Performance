
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 565.328 | 0.128508 | 955.591ms | 4604 | 30 | 2988.51 | 7766.67 | 0.0429 | 5.36011 | 1(Win) | true |
| Jsonifier (two-stage) | 502.42 | 0.630149 | 1036.15ms | 4604 | 4890 | 1.48297e+07 | 8739.14 | 0.390399 | 6.03472 | 2(Loss) | true |
| Glaze | 310.641 | 0.166449 | 1596.76ms | 4604 | 160 | 88559.4 | 14134.4 | 0.41293 | 9.77188 | 3(Loss) | true |
| simdjson (ondemand) | 169.004 | 0.331884 | 2750.99ms | 4604 | 30 | 223034 | 25980 | 0.0384763 | 17.9666 | 4(Loss) | true |
