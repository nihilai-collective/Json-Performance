
----
### Discord Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20741.3 | 0.0607745 | 1173.6ms | 94370 | 640 | 4450.61 | 4339.09 | 0.000432116 | 0.246997 | 0.894532 | 0.132871 | 0.000118831 | 8.44416e-06 | 4.58634e-06 | 1(Win) | true |
| Glaze | 7121.87 | 0.0571304 | 2012.49ms | 94370 | 1280 | 66715.3 | 12636.9 | 0.0359989 | 0.711647 | 3.60407 | 0.605966 | 0.000303327 | 7.2272e-06 | 3.61774e-06 | 2(Loss) | true |
| simdjson (reflection) | 560.819 | 0.172497 | 8603.11ms | 94370 | 1280 | 9.80836e+07 | 160477 | 0.166733 | 8.98391 | 38.8305 | 7.53866 | 0.02249 | 0.00883082 | 0.000318974 | 3(Loss) | true |
