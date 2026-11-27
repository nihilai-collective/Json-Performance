
----
### Random Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 13652.9 | 0.0165609 | 3964.37ms | 461466 | 2560 | 72952.2 | 32234.2 | 0.0763721 | 0.376963 | 2.02795 | 0.131947 | 7.75551e-06 | 1.01325e-05 | 8.6875e-06 | 1(Win) | true |
| simdjson (stage-1) | 12060.3 | 0.0307862 | 4368.29ms | 461466 | 1280 | 161542 | 36490.6 | 0.00637965 | 0.422061 | 2.35067 | 0.0920372 | 3.11914e-05 | 4.50162e-06 | 2.92207e-06 | 2(Loss) | true |
