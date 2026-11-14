
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18355.2 | 0.050257 | 7331.19ms | 5373214 | 640 | 1.25986e+07 | 279174 | 0.0154326 | 0.274664 | 1.42166 | 0.0539043 | 0.000789868 | 0.0195626 | 3.57764e-06 | 1(Win) | true |
| simdjson (stage-1) | 15514.3 | 0.0404189 | 8698.31ms | 5373214 | 80 | 1.42582e+06 | 330295 | 0.0190131 | 0.331497 | 1.41698 | 0.0578105 | 0.000929546 | 0.019574 | 9.80326e-06 | 2(Loss) | true |
