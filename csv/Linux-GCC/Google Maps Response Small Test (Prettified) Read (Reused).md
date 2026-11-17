
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3403.9 | 0.0740976 | 1026.41ms | 9378 | 160 | 606.45 | 2627.44 | 0.025459 | 1.50938 | 6.91523 | 0.991043 | 0.00159082 | 1.86607e-05 | 0 | 1(Win) | true |
| Jsonifier | 3273.96 | 0.0432053 | 1033.75ms | 9378 | 4890 | 6811.72 | 2731.72 | 0.117287 | 1.56642 | 6.98262 | 1.33301 | 0.00241559 | 2.24604e-05 | 6.12756e-06 | 2(Loss) | true |
| simdjson (reflection) | 3102.23 | 0.0450078 | 1046.69ms | 9378 | 4890 | 8232.99 | 2882.95 | 0.0497512 | 1.6407 | 6.68693 | 0.956601 | 0.000910149 | 2.73014e-05 | 5.97491e-06 | 3(Loss) | true |
| simdjson (ondemand) | 2392.42 | 0.0386539 | 1132.46ms | 9378 | 160 | 334.08 | 3738.29 | 0.044492 | 2.13726 | 8.38676 | 1.37375 | 0.00117762 | 2.13265e-05 | 1.99936e-06 | 4(Loss) | true |
| Glaze | 1999.69 | 0.0624819 | 1203.3ms | 9378 | 80 | 624.734 | 4472.48 | 0.0156537 | 2.55278 | 8.81926 | 1.66112 | 0.00389342 | 1.73278e-05 | 0 | 5(Loss) | true |
