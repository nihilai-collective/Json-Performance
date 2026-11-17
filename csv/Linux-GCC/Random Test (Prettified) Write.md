
----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24798.7 | 0.0903258 | 3224.11ms | 837491 | 2560 | 2.16653e+06 | 32207 | 0.19512 | 0.0997239 | 1(Win) | true |
| Glaze | 3945.44 | 0.395616 | 5285.55ms | 837491 | 30 | 1.92415e+07 | 202434 | 0.244809 | 0.627417 | 2(Loss) | true |
| simdjson (reflection) | 578.894 | 0.103999 | 8839.14ms | 837491 | 30 | 6.17651e+07 | 1.37969e+06 | 0.437775 | 4.27671 | 3(Loss) | true |
