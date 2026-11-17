
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1149.61 | 0.0685925 | 9711.77ms | 1834197 | 80 | 8.71431e+07 | 1.52158e+06 | 0.152249 | 2.15356 | 1(Win) | true |
| Glaze | 593.475 | 0.0840723 | 9159.66ms | 1833577 | 30 | 1.84086e+08 | 2.94643e+06 | 0.593722 | 4.17166 | 2(Loss) | true |
