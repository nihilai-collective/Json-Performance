
----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14455.1 | 0.115359 | 3846.38ms | 461466 | 30 | 37005 | 30445.2 | 0.0272696 | 0.350161 | 1.53911 | 0.193592 | 0.000143456 | 0.00941702 | 3.79226e-05 | 1(Win) | true |
| simdjson (reflection) | 11613.6 | 0.440177 | 4555.51ms | 461466 | 1280 | 3.56132e+07 | 37894.3 | 0.0226689 | 0.435134 | 2.22218 | 0.309145 | 0.00161312 | 0.0123057 | 3.3421e-05 | 2(Loss) | true |
| Glaze | 5232.96 | 0.149948 | 9325.44ms | 461466 | 40 | 636097 | 84099.3 | 0.243369 | 0.969335 | 4.64554 | 0.711034 | 0.00904075 | 0.0148563 | 3.28843e-05 | 3(Loss) | true |
