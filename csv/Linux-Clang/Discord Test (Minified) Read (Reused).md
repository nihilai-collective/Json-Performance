
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1788.16 | 0.0222115 | 4067.24ms | 56369 | 1280 | 57073.6 | 30063.1 | 0.00835552 | 2.87942 | 13.3082 | 2.60819 | 0.00534566 | 1.00898e-05 | 2.61946e-06 | 1(Win) | true |
| simdjson (ondemand) | 1422.84 | 0.0210268 | 4878.08ms | 56369 | 4890 | 308620 | 37781.9 | 0.100603 | 3.60017 | 14.7972 | 2.37353 | 0.0131823 | 1.43627e-05 | 4.70534e-06 | 2(Loss) | true |
