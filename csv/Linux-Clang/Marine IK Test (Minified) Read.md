
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 615.719 | 0.109834 | 8657.69ms | 1834197 | 30 | 2.92094e+08 | 2.84095e+06 | 0.258088 | 4.02093 | 1(Win) | true |
| simdjson (ondemand) | 611.104 | 0.0622896 | 8863.45ms | 1834197 | 160 | 5.08644e+08 | 2.86241e+06 | 2.00179 | 4.0513 | 2(Loss) | true |
