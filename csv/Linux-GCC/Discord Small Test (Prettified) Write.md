
----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14446.2 | 0.164653 | 779.199ms | 7376 | 320 | 205.694 | 486.931 | 0.0860718 | 0.385626 | 1.15415 | 0.180586 | 0.000135999 | 2.75386e-05 | 3.38937e-06 | 1(Win) | true |
| Glaze | 3408.92 | 0.141212 | 946.007ms | 7376 | 2560 | 21736.4 | 2063.5 | 0.00626552 | 1.5124 | 4.11483 | 0.684382 | 0.00014516 | 4.31615e-05 | 1.4193e-05 | 2(Loss) | true |
| simdjson (reflection) | 502.858 | 0.139693 | 2143.77ms | 7376 | 2560 | 977552 | 13988.7 | 0.276581 | 10.0476 | 39.2732 | 7.99512 | 0.0139887 | 0.000326492 | 0.000175082 | 3(Loss) | true |
