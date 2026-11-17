
----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 977.837 | 0.0910259 | 9237.05ms | 83958 | 40 | 222219 | 81883.4 | 0.113848 | 5.26675 | 23.2811 | 4.92208 | 0.00711576 | 8.93304e-06 | 5.06205e-06 | 1(Win) | true |
| simdjson (ondemand) | 320.834 | 0.125088 | 6645.73ms | 83958 | 80 | 7.79621e+06 | 249564 | 0.112989 | 15.9241 | 87.9664 | 18.623 | 0.0279906 | 1.4144e-05 | 4.16875e-06 | 2(Loss) | true |
