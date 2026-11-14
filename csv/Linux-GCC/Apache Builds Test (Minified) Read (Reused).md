
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2310.16 | 0.139826 | 5910.32ms | 94653 | 80 | 238809 | 39074.4 | 0.0228678 | 2.20927 | 11.0843 | 1.98275 | 0.00596983 | 4.62215e-06 | 1.05649e-06 | 1(Win) | true |
| simdjson (ondemand) | 1644.23 | 0.0440091 | 7497ms | 94653 | 4890 | 2.85454e+06 | 54899.8 | 0.278375 | 3.1284 | 12.1054 | 2.24274 | 0.00840274 | 9.79792e-06 | 5.85715e-06 | 2(Loss) | true |
