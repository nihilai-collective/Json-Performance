
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2331.27 | 0.116018 | 9620.64ms | 7351818 | 80 | 9.73974e+08 | 3.00748e+06 | 0.217556 | 1.06194 | 1(Win) | true |
| simdjson (ondemand) | 2257.28 | 0.167723 | 9938.12ms | 7351818 | 160 | 4.34232e+09 | 3.10605e+06 | 0.222161 | 1.09676 | 2(Loss) | true |
