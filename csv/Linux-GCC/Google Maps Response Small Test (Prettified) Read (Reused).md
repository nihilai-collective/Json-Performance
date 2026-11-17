
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2826.97 | 0.0583857 | 1061.39ms | 9378 | 1280 | 4367.17 | 3163.65 | 0.137515 | 1.84464 | 8.47004 | 1.44732 | 0.000849145 | 2.23262e-05 | 1.66613e-06 | 1(Win) | true |
| simdjson (ondemand) | 2377.81 | 0.049353 | 1115.09ms | 9378 | 1280 | 4410.68 | 3761.26 | 0.127951 | 2.18902 | 9.22755 | 1.58296 | 0.00188923 | 1.8744e-05 | 1.41621e-06 | 2(Loss) | true |
