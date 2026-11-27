
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 767.601 | 0.0832546 | 864.955ms | 1213 | 4890 | 7697.97 | 1507.04 | 0.0451307 | 6.86214 | 35.8013 | 6.61171 | 0.00362602 | 0.000213266 | 2.52884e-05 | 1(Win) | true |
| simdjson (ondemand) | 369.203 | 0.0600643 | 1029.79ms | 1213 | 640 | 2266.75 | 3133.25 | 0.0769872 | 14.1513 | 57.8895 | 11.7164 | 0.0149487 | 0.000109491 | 7.72877e-06 | 2(Loss) | true |
