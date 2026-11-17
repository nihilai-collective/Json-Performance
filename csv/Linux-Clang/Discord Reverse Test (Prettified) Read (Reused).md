
----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 988.077 | 0.0268578 | 9157.44ms | 83958 | 1280 | 606308 | 81034.7 | 0.0141518 | 5.18864 | 23.564 | 4.90904 | 0.0067081 | 1.15292e-05 | 5.34121e-06 | 1(Win) | true |
| simdjson (ondemand) | 304.972 | 0.0569942 | 6981.14ms | 83958 | 640 | 1.433e+07 | 262544 | 0.00595888 | 16.7882 | 92.5015 | 18.5106 | 0.0229092 | 5.103e-05 | 3.26056e-05 | 2(Loss) | true |
