
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2791.9 | 0.343537 | 6920.73ms | 5373214 | 160 | 6.36115e+09 | 1.83541e+06 | 0.176088 | 1.80791 | 10.0444 | 2.05643 | 0.00314501 | 0.0280967 | 0.000544883 | 1(Win) | true |
| Jsonifier (two-stage) | 2672.22 | 0.606581 | 7269.17ms | 5373214 | 30 | 4.05904e+09 | 1.91762e+06 | 1.10836 | 1.87324 | 9.8315 | 1.68393 | 0.00466384 | 0.0524867 | 0.000120164 | 2(Loss) | true |
| simdjson (reflection) | 2113.26 | 0.625609 | 8728.81ms | 5373214 | 40 | 9.20514e+09 | 2.42483e+06 | 0.856099 | 2.37238 | 11.1739 | 1.82411 | 0.00403143 | 0.0514256 | 0.000145081 | 3(Loss) | true |
| simdjson (ondemand) | 2023.4 | 0.633054 | 9128.81ms | 5373214 | 40 | 1.02813e+10 | 2.53252e+06 | 0.136957 | 2.493 | 11.5823 | 2.00523 | 0.00495751 | 0.0512532 | 0.000182377 | 4(Loss) | true |
| Glaze | 1793.81 | 0.913845 | 9942.58ms | 5373214 | 80 | 5.45194e+10 | 2.85666e+06 | 1.2013 | 2.81431 | 13.8602 | 2.43499 | 0.0042179 | 0.0298044 | 0.000222355 | 5(Loss) | true |
