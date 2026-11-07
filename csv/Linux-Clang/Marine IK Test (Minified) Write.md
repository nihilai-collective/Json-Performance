
----
### Marine IK Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1259.68 | 0.0240151 | 8758.45ms | 1834197 | 320 | 3.55871e+07 | 1.38863e+06 | 0.0322638 | 1.96538 | 1(Win) | true |
| Glaze | 657.227 | 0.0276088 | 8251.51ms | 1833577 | 160 | 8.63341e+07 | 2.66062e+06 | 0.136873 | 3.76698 | 2(Loss) | true |
