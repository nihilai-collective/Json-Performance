
----
### Canada Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6099.53 | 0.0597675 | 6601.1ms | 6661989 | 40 | 1.55026e+07 | 1.04162e+06 | 0.0437342 | 0.828052 | 2.48939 | 0.117147 | 0.000111198 | 0.0280193 | 8.76615e-06 | 1(Win) | true |
| Glaze | 3305.5 | 0.0700533 | 5990.61ms | 6661897 | 160 | 2.90069e+08 | 1.92204e+06 | 0.110945 | 1.52272 | 4.33449 | 0.464354 | 0.00373771 | 0.0636043 | 0.00186125 | 2(Loss) | true |
| simdjson (reflection) | 445.055 | 0.384859 | 10072.6ms | 6661989 | 40 | 1.20738e+11 | 1.42755e+07 | 0.900933 | 11.3311 | 36.3504 | 4.85759 | 0.0133646 | 0.25507 | 0.0942898 | 3(Loss) | true |
