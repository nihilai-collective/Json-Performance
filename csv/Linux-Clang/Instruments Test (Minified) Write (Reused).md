
----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16638.7 | 0.0554468 | 1366.6ms | 108313 | 4890 | 57940.9 | 6208.15 | 0.0821035 | 0.305755 | 1.45658 | 0.197151 | 0.000165813 | 5.42055e-06 | 2.28453e-06 | 1(Win) | true |
| Glaze | 5184.31 | 0.0878299 | 2732.6ms | 108313 | 4890 | 1.49752e+06 | 19924.6 | 0.0462574 | 0.979958 | 3.21806 | 0.400866 | 0.000272193 | 2.27282e-05 | 1.33881e-05 | 2(Loss) | true |
