
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13593.9 | 0.462943 | 6620.23ms | 7351818 | 320 | 1.82433e+09 | 515762 | 0.524279 | 0.372544 | 1.60714 | 0.0869614 | 0.00224619 | 0.0211738 | 0.000429202 | 1(Win) | true |
| simdjson (stage-1) | 13309.3 | 0.726802 | 6765.66ms | 7351818 | 640 | 9.38186e+09 | 526791 | 0.0265701 | 0.385076 | 1.58986 | 0.0660413 | 0.00111118 | 0.0211919 | 0.000196183 | 2(Loss) | true |
