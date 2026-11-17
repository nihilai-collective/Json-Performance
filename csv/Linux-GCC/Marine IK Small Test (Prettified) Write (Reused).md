
----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7384.54 | 0.0639466 | 321.493ms | 24579 | 40 | 164.808 | 3174.25 | 0.0781725 | 0.332518 | 1(Win) | true |
| Glaze | 4117.02 | 0.083715 | 646.299ms | 24579 | 40 | 908.717 | 5693.52 | 0.339145 | 0.59856 | 2(Loss) | true |
| simdjson (reflection) | 524.101 | 0.123456 | 4528.83ms | 24893 | 4890 | 1.52918e+07 | 45296.2 | 0.0878778 | 4.72123 | 3(Loss) | true |
