
----
### Discord Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1928.3 | 0.0604695 | 984.709ms | 4857 | 320 | 675.164 | 2402.11 | 0.148658 | 2.71752 | 11.2771 | 2.09656 | 0.00198618 | 3.41003e-05 | 8.36422e-06 | 1(Win) | true |
| simdjson (ondemand) | 1721.51 | 0.0367809 | 1031.62ms | 4857 | 4890 | 4789.27 | 2690.65 | 0.0519963 | 3.04058 | 12.1604 | 2.08627 | 0.000773618 | 3.57884e-05 | 4.71564e-06 | 2(Loss) | true |
