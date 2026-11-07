
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1236.1 | 0.244122 | 446.216ms | 4604 | 2560 | 192493 | 3552.07 | 0.0309665 | 1.98823 | 1(Win) | true |
| Jsonifier (two-stage) | 1085.78 | 0.0989535 | 490.201ms | 4604 | 40 | 640.49 | 4043.85 | 0.116774 | 2.26524 | 2(Loss) | true |
| Glaze | 760.97 | 0.308487 | 669.392ms | 4604 | 640 | 202763 | 5769.89 | 0.346183 | 3.23887 | 3(Loss) | true |
| simdjson (ondemand) | 575.89 | 0.196196 | 850.582ms | 4604 | 1280 | 286405 | 7624.23 | 0.161242 | 4.28331 | 4(Loss) | true |
