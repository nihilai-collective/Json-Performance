
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1561.73 | 0.256096 | 7080.89ms | 1834197 | 160 | 1.31646e+09 | 1.12006e+06 | 0.263818 | 1(Win) | true |
| Glaze | 895.572 | 0.301418 | 6115.83ms | 1833577 | 80 | 2.77093e+09 | 1.95253e+06 | 0.0190853 | 2(Loss) | true |
