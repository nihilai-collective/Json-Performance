
----
### Canada Test (Prettified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18355.4 | 0.113652 | 7381.85ms | 5373214 | 320 | 3.22141e+07 | 279170 | 0.122415 | 0.274969 | 1.42166 | 0.0539043 | 0.000791468 | 0.0195641 | 2.44558e-06 | 1(Win) | true |
| simdjson (stage-1) | 15350 | 0.127389 | 8823.65ms | 5373214 | 320 | 5.78716e+07 | 333830 | 0.0260702 | 0.332169 | 1.41698 | 0.0578105 | 0.00092991 | 0.0195773 | 2.72358e-06 | 2(Loss) | true |
