
----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2080.27 | 0.019895 | 3654.4ms | 56369 | 4890 | 129253 | 25841.7 | 0.0900919 | 2.44785 | 11.1914 | 2.17196 | 0.00409408 | 1.17361e-05 | 3.88544e-06 | 1(Win) | true |
| simdjson (ondemand) | 1524.3 | 0.0268715 | 4628.59ms | 56369 | 4890 | 439170 | 35267.1 | 0.187963 | 3.35 | 13.6843 | 2.35276 | 0.00980401 | 1.76024e-05 | 9.35989e-06 | 2(Loss) | true |
