
----
### Discord Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20448.3 | 0.0547397 | 1182.12ms | 94370 | 2560 | 14859.4 | 4401.26 | 0.016248 | 0.251112 | 0.900244 | 0.134153 | 0.000112605 | 2.38589e-05 | 1.60811e-05 | 1(Win) | true |
| Glaze | 5947.07 | 0.060543 | 2268.23ms | 94370 | 4890 | 410486 | 15133.2 | 0.266421 | 0.848875 | 3.65836 | 0.618332 | 0.000338629 | 1.11903e-05 | 5.593e-06 | 2(Loss) | true |
| simdjson (reflection) | 558.33 | 0.13188 | 8668.78ms | 94370 | 2560 | 1.15687e+08 | 161192 | 0.337803 | 9.00698 | 38.8295 | 7.53837 | 0.0220025 | 0.0110758 | 0.000190474 | 3(Loss) | true |
