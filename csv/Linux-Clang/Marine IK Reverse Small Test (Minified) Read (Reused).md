
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1044.21 | 0.165649 | 503.999ms | 4604 | 2560 | 124197 | 4204.83 | 0.00347455 | 2.35597 | 1(Win) | true |
| Jsonifier (two-stage) | 910.079 | 0.162248 | 563.706ms | 4604 | 4890 | 299627 | 4824.54 | 0.0109949 | 2.70504 | 2(Loss) | true |
| Glaze | 775.573 | 0.155702 | 647.93ms | 4604 | 2560 | 198909 | 5661.25 | 0.0181022 | 3.17766 | 3(Loss) | true |
| simdjson (ondemand) | 561.805 | 0.108719 | 866.411ms | 4604 | 4890 | 353035 | 7815.37 | 0.114365 | 4.39078 | 4(Loss) | true |
