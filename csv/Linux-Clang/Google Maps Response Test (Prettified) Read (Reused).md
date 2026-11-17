
----
### Google Maps Response Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2592 | 0.060807 | 1742.88ms | 25388 | 160 | 5161.95 | 9341 | 0.175929 | 1.99596 | 8.78943 | 1.57712 | 0.00290861 | 5.66212e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2275.19 | 0.0289818 | 1845.84ms | 25388 | 2560 | 24350.8 | 10641.7 | 0.0140788 | 2.26228 | 9.78675 | 1.59938 | 0.00283072 | 8.78552e-06 | 1.80019e-06 | 2(Loss) | true |
