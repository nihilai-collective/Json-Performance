
----
### Random Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 17826.9 | 0.0444996 | 3225.43ms | 461466 | 80 | 9654.52 | 24686.8 | 0.00648079 | 0.284169 | 1.43424 | 0.22632 | 0.000209143 | 0.00593253 | 2.16159e-05 | 1(Win) | true |
| simdjson (reflection) | 11372 | 0.0287042 | 4639.54ms | 461466 | 2560 | 315889 | 38699.2 | 0.0287552 | 0.444601 | 2.23952 | 0.31803 | 0.00191028 | 0.010006 | 2.4229e-05 | 2(Loss) | true |
| Glaze | 5207 | 0.0250356 | 9254.71ms | 461466 | 4890 | 2.18942e+06 | 84518.6 | 0.0470519 | 0.970463 | 4.64554 | 0.711034 | 0.00908777 | 0.0126704 | 2.48328e-05 | 3(Loss) | true |
