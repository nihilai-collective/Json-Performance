
----
### Google Maps Response Test (Minified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11742.1 | 0.0957817 | 836.6ms | 11812 | 4890 | 4128.82 | 959.348 | 0.234633 | 0.449114 | 2.09118 | 0.342618 | 0.000109088 | 2.6177e-05 | 9.48742e-06 | 1(Win) | true |
| Glaze | 3733.83 | 0.202185 | 1040.54ms | 11812 | 1280 | 47626.1 | 3016.96 | 0.33767 | 1.37366 | 5.63986 | 0.82357 | 0.000398099 | 4.12716e-05 | 2.09004e-05 | 2(Loss) | true |
