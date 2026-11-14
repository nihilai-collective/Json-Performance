
----
### Random Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2513.34 | 0.0777698 | 7865.15ms | 676745 | 1280 | 5.1048e+07 | 256787 | 0.145231 | 1.9969 | 9.76068 | 1.74851 | 0.00406955 | 0.0108785 | 4.96286e-06 | 1(Win) | true |
| simdjson (ondemand) | 1844.26 | 0.0737244 | 5162.19ms | 676745 | 160 | 1.065e+07 | 349947 | 0.0961755 | 2.78622 | 10.9319 | 1.92954 | 0.00831169 | 0.01915 | 7.76234e-05 | 2(Loss) | true |
