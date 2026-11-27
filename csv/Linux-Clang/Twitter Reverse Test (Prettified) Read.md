
----
### Twitter Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 880.387 | 0.0935507 | 5083.41ms | 360584 | 320 | 4.27277e+07 | 390600 | 0.0419458 | 5.77262 | 20.9283 | 3.89334 | 0.0220377 | 0.00259525 | 3.87306e-05 | 1(Win) | true |
| simdjson (ondemand) | 394.073 | 0.103989 | 5543.07ms | 360584 | 320 | 2.63504e+08 | 872628 | 0.0974958 | 12.7872 | 52.8689 | 9.19521 | 0.0529535 | 0.00363581 | 0.00029415 | 2(Loss) | true |
