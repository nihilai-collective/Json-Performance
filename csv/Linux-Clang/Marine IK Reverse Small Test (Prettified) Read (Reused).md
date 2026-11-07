
----
### Marine IK Reverse Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3370.62 | 0.114561 | 619.003ms | 18245 | 4890 | 171022 | 5162.19 | 0.355046 | 0.730634 | 1(Win) | true |
| Jsonifier | 2760.32 | 0.135865 | 717.328ms | 18245 | 2560 | 187770 | 6303.54 | 0.00749151 | 0.893236 | 2(Loss) | true |
| simdjson (ondemand) | 2099.71 | 0.162129 | 921.654ms | 18245 | 40 | 7220.23 | 8286.77 | 0.036316 | 1.17456 | 3(Loss) | true |
| Glaze | 1990.48 | 0.19387 | 952.511ms | 18245 | 1280 | 367622 | 8741.5 | 0.0520057 | 1.2401 | 4(Loss) | true |
