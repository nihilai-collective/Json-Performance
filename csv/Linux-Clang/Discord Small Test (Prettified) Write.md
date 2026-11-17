
----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10906.3 | 0.229848 | 803.205ms | 7376 | 4890 | 10746.6 | 644.973 | 0.162724 | 0.492226 | 1.54745 | 0.281453 | 0.000171229 | 3.13014e-05 | 7.2362e-06 | 1(Win) | true |
| Glaze | 2780.36 | 0.325565 | 996.5ms | 7376 | 1280 | 86840.9 | 2530 | 0.505614 | 1.84737 | 4.54759 | 0.733731 | 0.00156663 | 3.47411e-05 | 6.67282e-06 | 2(Loss) | true |
