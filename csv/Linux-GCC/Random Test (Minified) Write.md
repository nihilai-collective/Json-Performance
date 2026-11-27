
----
### Random Test (Minified) Write Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14440.8 | 0.120863 | 3858.04ms | 461466 | 40 | 54267.9 | 30475.3 | 0.416954 | 0.35056 | 1.53813 | 0.19386 | 0.000147248 | 0.00960878 | 1.77695e-05 | 1(Win) | true |
| simdjson (reflection) | 11516.5 | 0.271129 | 4613.25ms | 461466 | 2560 | 2.74809e+07 | 38213.8 | 0.0699867 | 0.439718 | 2.22329 | 0.309397 | 0.00170604 | 0.0120958 | 2.17877e-05 | 2(Loss) | true |
| Glaze | 4556.56 | 0.213877 | 5374.05ms | 461466 | 2560 | 1.09238e+08 | 96583.4 | 0.0281797 | 1.10733 | 4.6601 | 0.714436 | 0.00904201 | 0.0442523 | 2.48546e-05 | 3(Loss) | true |
