
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6253.68 | 0.261344 | 760.829ms | 2889 | 30 | 39.7713 | 440.567 | 0.00756544 | 0.915334 | 3.66113 | 0.49775 | 0.000357679 | 2.3076e-05 | 0 | 1(Win) | true |
| Jsonifier (two-stage) | 6189.82 | 0.148788 | 758.601ms | 2889 | 80 | 35.0884 | 445.113 | 0.109403 | 0.90752 | 3.66113 | 0.49775 | 0.000346141 | 2.59605e-05 | 0 | 2(Loss) | true |
| simdjson (ondemand) | 5709.11 | 0.0895986 | 763.697ms | 2889 | 320 | 59.8288 | 482.591 | 0.399231 | 0.977705 | 3.82381 | 0.400831 | 0.000376428 | 2.27155e-05 | 0 | 3(Loss) | true |
| simdjson (reflection) | 5612.36 | 0.0762822 | 764.14ms | 2889 | 1280 | 179.499 | 490.91 | 0.708699 | 0.99892 | 3.81343 | 0.407061 | 0.000356957 | 3.92112e-05 | 5.94929e-06 | 4(Loss) | true |
| Glaze | 3183.97 | 0.152291 | 796.67ms | 2889 | 80 | 138.931 | 865.325 | 0.0925364 | 1.69798 | 7.17965 | 1.22603 | 0.000346141 | 2.59605e-05 | 1.29803e-05 | 5(Loss) | true |
