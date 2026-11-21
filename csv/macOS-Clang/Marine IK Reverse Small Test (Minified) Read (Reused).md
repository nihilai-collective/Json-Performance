
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 727.401 | 0.969847 | 776.24ms | 4604 | 160 | 548339 | 6036.17 | 1.57585 | 1(Win) | true |
| Jsonifier (two-stage) | 655.744 | 0.247341 | 949.247ms | 4604 | 80 | 21942.4 | 6695.77 | 0.974186 | 2(Loss) | true |
| Glaze | 425.265 | 0.184942 | 1228.96ms | 4604 | 4890 | 1.78291e+06 | 10324.7 | 0.114731 | 3(Loss) | true |
| simdjson (ondemand) | 300.533 | 0.294684 | 1521.17ms | 4604 | 2560 | 4.74503e+06 | 14609.8 | 0.322792 | 4(Loss) | true |
