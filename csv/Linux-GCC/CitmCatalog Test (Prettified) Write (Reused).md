
----
### CitmCatalog Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18556.8 | 0.0289021 | 8209.26ms | 1439562 | 2560 | 1.17045e+06 | 73982.1 | 0.0763269 | 0.274819 | 0.693874 | 0.0752278 | 0.000506145 | 0.0186149 | 3.52185e-06 | 1(Win) | true |
| Glaze | 7923.49 | 0.0588382 | 9274.41ms | 1439584 | 2560 | 2.66073e+07 | 173269 | 0.00766164 | 0.638453 | 3.11679 | 0.497885 | 0.000866907 | 0.0181163 | 1.29095e-05 | 2(Loss) | true |
| simdjson (reflection) | 579.554 | 0.934702 | 7356.16ms | 1439562 | 40 | 1.96101e+10 | 2.36884e+06 | 0.50253 | 8.70069 | 35.5655 | 6.42567 | 0.0159322 | 0.311955 | 0.0160851 | 3(Loss) | true |
