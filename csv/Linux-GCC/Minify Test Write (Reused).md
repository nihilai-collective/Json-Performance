
----
### Minify Test Write (Reused) Results [(Here is the data we used for this test)](./json/Minify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Minify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10329.2 | 0.0695027 | 5034.83ms | 466906 | 2560 | 2.2981e+06 | 43108.5 | 0.113268 | 0.496037 | 1.97287 | 0.0755185 | 3.08187e-05 | 0.000162155 | 6.9398e-06 | 1(Win) | true |
| simdjson (ondemand) | 9371.36 | 0.0343271 | 5497.34ms | 466906 | 320 | 85128.9 | 47514.6 | 0.0824265 | 0.549907 | 2.07055 | 0.0433279 | 8.24376e-05 | 0.00153828 | 7.73041e-06 | 2(Loss) | true |
| Glaze | 2535.42 | 0.0448887 | 9383.41ms | 466906 | 640 | 3.97754e+06 | 175622 | 0.0601417 | 2.02447 | 8.75336 | 1.96118 | 0.00248127 | 0.000993876 | 2.96199e-05 | 3(Loss) | true |
