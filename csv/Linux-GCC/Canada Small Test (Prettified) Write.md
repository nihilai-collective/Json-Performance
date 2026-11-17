
----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5669.37 | 0.468523 | 251.352ms | 14795 | 640 | 87016.6 | 2488.74 | 0.0555945 | 0.431915 | 1(Win) | true |
| Glaze | 3294.19 | 0.0844649 | 458.084ms | 14795 | 40 | 523.533 | 4283.18 | 0.0251045 | 0.746953 | 2(Loss) | true |
| simdjson (reflection) | 403.043 | 0.0898402 | 3529.66ms | 14795 | 2560 | 2.53226e+06 | 35007.7 | 0.598992 | 6.13809 | 3(Loss) | true |
