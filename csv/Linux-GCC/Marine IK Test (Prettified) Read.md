
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20617.3 | 0.141483 | 9087.58ms | 7351818 | 80 | 1.85193e+07 | 340066 | 0.324852 | 0.120073 | 1(Win) | true |
| simdjson (stage-1) | 16686.6 | 0.181226 | 5318.7ms | 7351818 | 40 | 2.31929e+07 | 420173 | 0.258959 | 0.148357 | 2(Loss) | true |
