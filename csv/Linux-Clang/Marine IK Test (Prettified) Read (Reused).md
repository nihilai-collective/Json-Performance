
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2818.83 | 0.619571 | 8719.7ms | 7351818 | 30 | 7.1245e+09 | 2.48729e+06 | 0.319887 | 1.78155 | 7.84504 | 1.41081 | 0.00970429 | 0.0544137 | 0.00171535 | 1(Win) | true |
| Jsonifier | 2669.57 | 0.504741 | 8902.43ms | 7351818 | 30 | 5.27187e+09 | 2.62636e+06 | 0.248612 | 1.88643 | 8.68479 | 2.01123 | 0.00667912 | 0.0275031 | 0.0017093 | 2(Loss) | true |
| simdjson (ondemand) | 2292.22 | 0.168057 | 5009.69ms | 7351818 | 30 | 7.92701e+08 | 3.05871e+06 | 0.714555 | 2.19535 | 9.45137 | 1.43645 | 0.00986308 | 0.0535843 | 0.00251752 | 3(Loss) | true |
| Glaze | 2225.59 | 0.193745 | 5102.79ms | 7351818 | 30 | 1.11758e+09 | 3.15028e+06 | 0.063977 | 2.25685 | 10.2817 | 2.06802 | 0.00919606 | 0.0274235 | 0.0019003 | 4(Loss) | true |
