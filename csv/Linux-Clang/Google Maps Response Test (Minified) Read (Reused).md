
----
### Google Maps Response Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1431.03 | 0.0245224 | 1560.08ms | 11812 | 4890 | 18221.5 | 7871.8 | 0.122031 | 3.61544 | 17.0348 | 3.29631 | 0.00486816 | 3.19941e-05 | 1.37464e-05 | 1(Win) | true |
| simdjson (ondemand) | 1113.41 | 0.127013 | 1785.53ms | 11812 | 160 | 26421.2 | 10117.4 | 0.0101939 | 4.64178 | 19.6626 | 3.36074 | 0.00761355 | 1.85193e-05 | 3.17474e-06 | 2(Loss) | true |
