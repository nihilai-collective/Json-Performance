
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3203.66 | 0.0185246 | 2758.76ms | 56369 | 4890 | 47249.3 | 16780.1 | 0.0893247 | 1.58088 | 7.42678 | 1.34424 | 0.00184735 | 1.74246e-05 | 9.07328e-06 | 1(Win) | true |
| Glaze | 2813.03 | 0.102241 | 3013.22ms | 56369 | 2560 | 977277 | 19110.2 | 0.0159718 | 1.80001 | 8.95624 | 1.756 | 0.00210162 | 2.90011e-05 | 1.54881e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2452.76 | 0.0164057 | 3285.58ms | 56369 | 4890 | 63222.3 | 21917.2 | 0.0168688 | 2.0643 | 10.2707 | 1.66993 | 0.00216581 | 1.79978e-05 | 9.31998e-06 | 3(Loss) | true |
| simdjson (reflection) | 1814.11 | 0.0338221 | 4087.21ms | 56369 | 2560 | 257153 | 29633 | 0.012615 | 2.78755 | 12.2458 | 2.05253 | 0.00369679 | 3.494e-05 | 2.20922e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1632.76 | 0.0963915 | 4462.47ms | 56369 | 4890 | 4.92515e+06 | 32924.3 | 0.0312761 | 3.10862 | 12.8392 | 2.29495 | 0.00851334 | 7.94611e-05 | 5.24226e-05 | 5(Loss) | true |
