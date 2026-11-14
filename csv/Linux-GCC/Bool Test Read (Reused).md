
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2463.53 | 0.214521 | 768.201ms | 905 | 640 | 361.493 | 350.341 | 1.10182 | 2.31272 | 11.0365 | 1.73039 | 0.00110843 | 0.000155387 | 6.90608e-06 | 1(Win) | true |
| Glaze | 1874.95 | 0.13773 | 777.114ms | 905 | 4890 | 1965.56 | 460.318 | 0.424516 | 2.96269 | 13.6652 | 2.06519 | 0.0011348 | 0.0001053 | 2.55341e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 601.431 | 0.115376 | 878.73ms | 905 | 4890 | 13404.9 | 1435.04 | 0.185619 | 8.69245 | 42.2144 | 4.29171 | 0.00850784 | 0.000147556 | 1.69474e-05 | 3(Loss) | true |
| simdjson (ondemand) | 222.558 | 0.159312 | 1120.1ms | 905 | 40 | 1526.74 | 3877.97 | 0.063352 | 22.9635 | 104.842 | 9.68508 | 0.0879282 | 0.000276243 | 0 | 4(Loss) | true |
