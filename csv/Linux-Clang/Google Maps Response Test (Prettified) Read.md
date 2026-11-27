
----
### Google Maps Response Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2474.91 | 0.0757637 | 1724.96ms | 25388 | 80 | 4394.93 | 9782.95 | 0.0465311 | 2.09055 | 9.37266 | 1.63885 | 0.00292412 | 8.86245e-06 | 2.46179e-06 | 1(Win) | true |
| simdjson (ondemand) | 2104.06 | 0.150878 | 1916.01ms | 25388 | 80 | 24114.7 | 11507.2 | 0.127366 | 2.40937 | 10.0874 | 1.67384 | 0.00400484 | 9.84717e-06 | 5.41594e-06 | 2(Loss) | true |
