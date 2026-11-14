
----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8941.14 | 0.0874633 | 751.927ms | 2963 | 80 | 6.1125 | 316.038 | 0.202124 | 0.648536 | 1.48059 | 0.233885 | 0.000337496 | 1.26561e-05 | 0 | 1(Win) | true |
| simdjson (reflection) | 6736.54 | 0.066055 | 762.69ms | 2963 | 1280 | 98.2677 | 419.464 | 0.111501 | 0.838752 | 1.92035 | 0.289909 | 0.00033855 | 2.71579e-05 | 5.27337e-06 | 2(Loss) | true |
| Glaze | 5788.04 | 0.192993 | 769.309ms | 2963 | 640 | 568.15 | 488.203 | 0.463008 | 0.964609 | 3.02396 | 0.469119 | 0.000337496 | 8.17373e-05 | 2.68942e-05 | 3(Loss) | true |
