
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 20631.7 | 0.0823938 | 8636.49ms | 7351818 | 320 | 2.50875e+07 | 339829 | 0.213024 | 0.119989 | 1(Win) | true |
| simdjson (stage-1) | 19358.8 | 0.0650592 | 9388.72ms | 7351818 | 640 | 3.55329e+07 | 362174 | 0.0444444 | 0.12788 | 2(Loss) | true |
