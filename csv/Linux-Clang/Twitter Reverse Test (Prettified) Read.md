
----
### Twitter Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 870.931 | 0.0712105 | 5115.99ms | 360584 | 320 | 2.52978e+07 | 394842 | 0.0349662 | 5.83843 | 21.7105 | 4.07989 | 0.0184244 | 0.000484388 | 6.35254e-05 | 1(Win) | true |
| simdjson (ondemand) | 387.672 | 0.140763 | 5655.39ms | 360584 | 160 | 2.49449e+08 | 887038 | 0.0806429 | 13.0186 | 52.9005 | 9.20678 | 0.0572644 | 0.000343696 | 7.81718e-05 | 2(Loss) | true |
