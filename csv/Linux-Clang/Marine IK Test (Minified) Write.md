
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1269.51 | 0.14071 | 9185.79ms | 1922245 | 40 | 1.6514e+08 | 1.44401e+06 | 2.4611 | 1.95012 | 1(Win) | true |
| Glaze | 658.443 | 0.0468206 | 8483.46ms | 1833577 | 40 | 6.18438e+07 | 2.65571e+06 | 0.0384131 | 3.76005 | 2(Loss) | true |
