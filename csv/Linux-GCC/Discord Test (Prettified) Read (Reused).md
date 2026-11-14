
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2525.95 | 0.0577326 | 4235.27ms | 83958 | 160 | 53584.3 | 31698.5 | 0.00640845 | 2.04049 | 9.18229 | 1.69531 | 0.00390962 | 4.98761e-06 | 5.95536e-07 | 1(Win) | true |
| simdjson (ondemand) | 2177.47 | 0.107074 | 4778.15ms | 83958 | 80 | 124015 | 36771.4 | 0.0348218 | 2.36743 | 9.61962 | 1.58238 | 0.00723948 | 2.84368e-05 | 2.00993e-05 | 2(Loss) | true |
