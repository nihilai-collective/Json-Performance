
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1163.74 | 0.24817 | 5736.09ms | 264040 | 40 | 1.15341e+07 | 216378 | 0.765509 | 2.6115 | 1(Win) | true |
| simdjson (ondemand) | 950.208 | 0.537785 | 6837.77ms | 264040 | 30 | 6.09314e+07 | 265003 | 0.111823 | 3.1983 | 2(Loss) | true |
