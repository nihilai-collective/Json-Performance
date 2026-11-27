
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2635.84 | 0.0685277 | 1095.38ms | 9378 | 1280 | 6920.31 | 3393.06 | 0.214707 | 1.95942 | 8.71316 | 1.48635 | 0.00130791 | 1.74111e-05 | 2.99904e-06 | 1(Win) | true |
| simdjson (ondemand) | 2326.76 | 0.0492196 | 1134.74ms | 9378 | 4890 | 17502.5 | 3843.78 | 0.221172 | 2.21947 | 9.42514 | 1.51866 | 0.0015371 | 2.61675e-05 | 9.87823e-06 | 2(Loss) | true |
