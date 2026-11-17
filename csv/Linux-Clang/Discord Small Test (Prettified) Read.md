
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1855.02 | 0.0763514 | 1073.06ms | 6701 | 160 | 1106.97 | 3445.01 | 0.0595417 | 2.81096 | 11.1013 | 2.08566 | 0.00153895 | 3.54425e-05 | 1.02597e-05 | 1(Win) | true |
| simdjson (ondemand) | 1807.62 | 0.0433199 | 1079.16ms | 6701 | 2560 | 6004.52 | 3535.34 | 0.0331805 | 2.87822 | 11.6602 | 1.92344 | 0.000876268 | 3.27027e-05 | 3.90567e-06 | 2(Loss) | true |
