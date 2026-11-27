
----
### Instruments Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16019.8 | 0.141087 | 742.458ms | 4669 | 40 | 6.15128 | 277.95 | 0.0539957 | 0.375337 | 1.23752 | 0.152281 | 0.000214179 | 1.07089e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 11760.3 | 0.424777 | 755.343ms | 4669 | 4890 | 12648.7 | 378.623 | 0.145234 | 0.487993 | 1.51381 | 0.16299 | 0.000214441 | 2.54036e-05 | 2.45276e-06 | 2(Loss) | true |
| Glaze | 4587.13 | 0.147318 | 816.321ms | 4669 | 4890 | 9999.63 | 970.694 | 0.22259 | 1.16877 | 2.95716 | 0.386378 | 0.000214529 | 2.22063e-05 | 5.25592e-06 | 3(Loss) | true |
