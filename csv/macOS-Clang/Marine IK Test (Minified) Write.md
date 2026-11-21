
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1518.86 | 0.367065 | 7853.99ms | 1922245 | 40 | 7.85105e+08 | 1.20695e+06 | 0.00599269 | 1(Win) | true |
| Glaze | 860.365 | 0.354008 | 6479.09ms | 1833577 | 80 | 4.14143e+09 | 2.03243e+06 | 0.145133 | 2(Loss) | true |
