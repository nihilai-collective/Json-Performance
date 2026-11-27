
----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19627.5 | 0.336373 | 1250.32ms | 108313 | 80 | 25070.5 | 5262.79 | 0.133901 | 0.258945 | 1.171 | 0.147591 | 5.97805e-05 | 7.15519e-06 | 5.30869e-06 | 1(Win) | true |
| simdjson (reflection) | 16840.2 | 0.0624563 | 1347.6ms | 108313 | 160 | 2348.23 | 6133.86 | 0.0657798 | 0.302339 | 1.44602 | 0.154755 | 6.43967e-05 | 4.21233e-06 | 2.76975e-06 | 2(Loss) | true |
| Glaze | 6837.82 | 0.25847 | 2259.4ms | 108313 | 160 | 243930 | 15106.5 | 0.404645 | 0.754683 | 2.97166 | 0.386768 | 0.000275359 | 2.25042e-06 | 4.61625e-07 | 3(Loss) | true |
