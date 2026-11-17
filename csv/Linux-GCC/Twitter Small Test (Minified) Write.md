
----
### Twitter Small Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8931.82 | 0.116441 | 756.603ms | 2963 | 4890 | 663.6 | 316.367 | 0.292359 | 0.648065 | 1.48059 | 0.233885 | 0.00033791 | 7.76447e-05 | 4.3274e-05 | 1(Win) | true |
| simdjson (reflection) | 6786.47 | 0.0530955 | 764.569ms | 2963 | 1280 | 62.5606 | 416.378 | 0.0082564 | 0.829783 | 1.92609 | 0.291596 | 0.000337496 | 2.97945e-05 | 6.59171e-06 | 2(Loss) | true |
| Glaze | 5497.76 | 0.0946317 | 775.409ms | 2963 | 2560 | 605.627 | 513.98 | 0.156196 | 0.999527 | 2.97401 | 0.458657 | 0.000338023 | 8.13418e-05 | 3.78364e-05 | 3(Loss) | true |
