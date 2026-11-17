
----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20192 | 0.129005 | 1189.07ms | 94370 | 640 | 21159.3 | 4457.13 | 0.277149 | 0.250973 | 0.900244 | 0.134153 | 0.00010628 | 3.95716e-06 | 1.67227e-06 | 1(Win) | true |
| Glaze | 5913.52 | 0.0850356 | 2269.4ms | 94370 | 2560 | 428764 | 15219.1 | 0.0233898 | 0.854808 | 3.65836 | 0.618332 | 0.00039447 | 1.65489e-05 | 8.96571e-06 | 2(Loss) | true |
| simdjson (reflection) | 546.362 | 0.159605 | 8850.01ms | 94370 | 2560 | 1.76947e+08 | 164723 | 1.33692 | 9.21422 | 38.8295 | 7.53837 | 0.022649 | 0.0143238 | 0.00031536 | 3(Loss) | true |
