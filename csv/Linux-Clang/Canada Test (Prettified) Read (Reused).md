
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2046.27 | 0.187893 | 8849.55ms | 5212421 | 30 | 6.2502e+08 | 2.42927e+06 | 0.415357 | 2.47985 | 11.3277 | 1.7836 | 0.00997131 | 0.0512934 | 0.000284737 | 1(Win) | true |
| Jsonifier (generic) | 2017.23 | 0.3464 | 8855.63ms | 5212421 | 40 | 2.91461e+09 | 2.46424e+06 | 0.0683067 | 2.52309 | 11.7331 | 2.08631 | 0.00999507 | 0.0511405 | 0.000441134 | 2(Loss) | true |
