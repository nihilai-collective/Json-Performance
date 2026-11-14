
----
### Canada Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 907.613 | 0.049153 | 1312.07ms | 4630 | 4890 | 27962 | 4864.97 | 0.134908 | 5.60591 | 27.6091 | 4.62916 | 0.00160914 | 7.34076e-05 | 3.03878e-05 | 1(Win) | true |
| Jsonifier (generic) | 865.142 | 0.066854 | 1333.95ms | 4630 | 4890 | 56931.2 | 5103.8 | 0.0632118 | 5.90364 | 28.3559 | 5.30367 | 0.00207675 | 8.3213e-05 | 3.78964e-05 | 2(Loss) | true |
