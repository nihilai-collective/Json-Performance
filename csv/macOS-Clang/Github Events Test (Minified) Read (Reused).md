
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2574.41 | 0.162009 | 2513.27ms | 53331 | 640 | 655639 | 19756.1 | 0.00628009 | 1(Win) | true |
| Jsonifier (two-stage) | 2004.02 | 0.0448152 | 3180.01ms | 53331 | 30 | 3880.86 | 25379.2 | 0.0543457 | 2(Loss) | true |
| Glaze | 1969.9 | 0.0988189 | 3137.36ms | 53331 | 2560 | 1.66644e+06 | 25818.8 | 0.205553 | 3(Loss) | true |
| simdjson (ondemand) | 1012.28 | 0.14304 | 5581.41ms | 53331 | 320 | 1.65281e+06 | 50243.2 | 0.0709107 | 4(Loss) | true |
