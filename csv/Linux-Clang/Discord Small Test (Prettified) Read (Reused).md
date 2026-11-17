
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2860.16 | 0.057589 | 256.554ms | 6701 | 80 | 132.454 | 2234.34 | 0.490458 | 0.855048 | 1(Win) | true |
| Glaze | 2243.96 | 0.429311 | 318.605ms | 6701 | 30 | 4484.51 | 2847.9 | 0.714684 | 1.0931 | 2(Loss) | true |
| Jsonifier | 2052.43 | 0.0751819 | 348.391ms | 6701 | 160 | 876.778 | 3113.66 | 0.0100354 | 1.19599 | 3(Loss) | true |
| simdjson (ondemand) | 1136.81 | 0.142347 | 586.975ms | 6701 | 4890 | 313117 | 5621.49 | 0.22404 | 2.16624 | 4(Loss) | true |
