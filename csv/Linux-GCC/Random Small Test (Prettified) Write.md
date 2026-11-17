
----
### Random Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 25479 | 0.160567 | 757.837ms | 9255 | 160 | 49.5017 | 346.413 | 0.0432822 | 0.225525 | 0.931172 | 0.143922 | 0.00010805 | 4.05186e-06 | 0 | 1(Win) | true |
| Glaze | 3659.55 | 0.148137 | 985.075ms | 9255 | 1280 | 16339.4 | 2411.84 | 0.0317343 | 1.40416 | 4.80886 | 0.812858 | 0.000168912 | 3.25837e-05 | 9.53876e-06 | 2(Loss) | true |
| simdjson (reflection) | 527.287 | 0.0972986 | 2415.62ms | 9255 | 4890 | 1.29712e+06 | 16739 | 0.488054 | 9.5822 | 37.9983 | 7.26375 | 0.0205013 | 0.000241466 | 0.000150297 | 3(Loss) | true |
