
----
### Google Maps Response Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20762.7 | 0.087952 | 875.193ms | 31235 | 160 | 254.757 | 1434.69 | 0.133482 | 0.250669 | 0.668225 | 0.0968465 | 3.20154e-05 | 1.28061e-05 | 7.60365e-06 | 1(Win) | true |
| Glaze | 6506.54 | 0.0647441 | 1195.13ms | 31235 | 4890 | 42962.8 | 4578.17 | 0.0479016 | 0.781859 | 3.75185 | 0.631087 | 0.000709445 | 1.83254e-05 | 8.93026e-06 | 2(Loss) | true |
| simdjson (reflection) | 529.849 | 0.170258 | 6390.75ms | 31235 | 2560 | 2.34549e+07 | 56219.8 | 0.00676381 | 9.46397 | 38.2381 | 7.0414 | 0.0157081 | 0.000213352 | 0.000145145 | 3(Loss) | true |
