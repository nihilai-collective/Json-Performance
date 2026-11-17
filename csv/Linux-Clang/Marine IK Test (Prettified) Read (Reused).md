
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2772 | 0.148496 | 8679.46ms | 7351818 | 40 | 5.64276e+08 | 2.52931e+06 | 0.18844 | 1.80582 | 7.96592 | 1.48998 | 0.00959917 | 0.0544113 | 0.00186654 | 1(Win) | true |
| Jsonifier | 2709.87 | 0.134935 | 8827.06ms | 7351818 | 40 | 4.87528e+08 | 2.58729e+06 | 1.66207 | 1.85737 | 8.73079 | 2.07759 | 0.00671972 | 0.0274603 | 0.00252835 | 2(Loss) | true |
| simdjson (ondemand) | 2305.63 | 0.0842984 | 10228.4ms | 7351818 | 160 | 1.05141e+09 | 3.04093e+06 | 0.0603268 | 2.17968 | 9.45137 | 1.43645 | 0.00990936 | 0.0536755 | 0.00303372 | 3(Loss) | true |
| Glaze | 2248.26 | 0.0958293 | 5066.7ms | 7351818 | 40 | 3.57234e+08 | 3.11852e+06 | 0.179205 | 2.23359 | 10.2817 | 2.06801 | 0.0089472 | 0.0274698 | 0.00103952 | 4(Loss) | true |
