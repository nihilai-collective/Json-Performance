
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2402.76 | 0.163593 | 9903.38ms | 7351818 | 40 | 9.11505e+08 | 2.918e+06 | 0.268375 | 1.03036 | 1(Win) | true |
| simdjson (ondemand) | 2245.88 | 0.165137 | 5147.27ms | 7351818 | 80 | 2.12614e+09 | 3.12182e+06 | 0.270176 | 1.10233 | 2(Loss) | true |
