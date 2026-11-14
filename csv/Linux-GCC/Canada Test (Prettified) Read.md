
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18672.6 | 0.0572913 | 7282.83ms | 5373214 | 640 | 1.58204e+07 | 274429 | 0.160406 | 0.273837 | 1.37324 | 0.0519539 | 0.000768053 | 0.0195647 | 2.1321e-06 | 1(Win) | true |
| simdjson (stage-1) | 15264.2 | 0.0582586 | 8826.34ms | 5373214 | 640 | 2.44805e+07 | 335707 | 0.0547238 | 0.33626 | 1.59197 | 0.0578107 | 0.000948089 | 0.0195707 | 7.35768e-06 | 2(Loss) | true |
