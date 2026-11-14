
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1826.51 | 0.0360992 | 998.524ms | 4857 | 2560 | 2145.5 | 2535.98 | 0.000292662 | 2.86665 | 11.624 | 2.21701 | 0.00216303 | 4.44751e-05 | 6.19274e-06 | 1(Win) | true |
| simdjson (ondemand) | 1650.89 | 0.0509949 | 1022.46ms | 4857 | 320 | 655.097 | 2805.76 | 0.0202667 | 3.16596 | 13.1493 | 2.1085 | 0.0010333 | 6.36967e-05 | 1.2868e-06 | 2(Loss) | true |
