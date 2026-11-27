
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 11141.3 | 0.0663704 | 1654.4ms | 108313 | 320 | 12116.8 | 9271.39 | 0.0271595 | 0.46396 | 2.47339 | 0.179369 | 4.0623e-05 | 1.15406e-06 | 5.77031e-08 | 1(Win) | true |
| simdjson (stage-1) | 10044.1 | 0.0376886 | 1752ms | 108313 | 2560 | 38459.3 | 10284.2 | 0.101573 | 0.514468 | 2.45756 | 0.108907 | 3.08784e-05 | 2.12059e-06 | 8.79973e-07 | 2(Loss) | true |
