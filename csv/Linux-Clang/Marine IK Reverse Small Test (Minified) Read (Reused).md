
----
### Marine IK Reverse Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 963.178 | 0.186162 | 552.746ms | 4604 | 4890 | 352166 | 4558.57 | 0.477235 | 2.55481 | 1(Win) | true |
| Jsonifier (two-stage) | 895.036 | 0.128094 | 589.09ms | 4604 | 30 | 1184.59 | 4905.63 | 0.0210598 | 2.74909 | 2(Loss) | true |
| Glaze | 665.264 | 0.337954 | 750.623ms | 4604 | 1280 | 636809 | 6599.97 | 0.224967 | 3.70581 | 3(Loss) | true |
| simdjson (ondemand) | 544.141 | 0.085632 | 884.746ms | 4604 | 40 | 1909.76 | 8069.07 | 0.280429 | 4.53291 | 4(Loss) | true |
