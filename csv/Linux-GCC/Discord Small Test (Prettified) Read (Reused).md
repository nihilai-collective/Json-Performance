
----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3414.09 | 0.119768 | 932.749ms | 6701 | 1280 | 6433.14 | 1871.82 | 0.0563773 | 1.54082 | 6.02686 | 1.05611 | 0.000542013 | 4.27875e-05 | 1.01431e-05 | 1(Win) | true |
| Glaze | 2696.8 | 0.109731 | 985.533ms | 6701 | 1280 | 8654.6 | 2369.68 | 0.366099 | 1.95262 | 8.42934 | 1.64632 | 0.000949602 | 2.01696e-05 | 4.31372e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2665.11 | 0.184326 | 986.009ms | 6701 | 80 | 1562.83 | 2397.86 | 0.031789 | 1.96716 | 8.24071 | 1.18699 | 0.000936427 | 4.47694e-05 | 3.73079e-06 | 3(Loss) | true |
| simdjson (reflection) | 2372.57 | 0.0523325 | 1022.17ms | 6701 | 640 | 1271.64 | 2693.53 | 0.318322 | 2.16501 | 8.75989 | 1.34338 | 0.000844557 | 4.96661e-05 | 6.06253e-06 | 4(Loss) | true |
| simdjson (ondemand) | 2128.64 | 0.0718966 | 1044.12ms | 6701 | 640 | 2981.74 | 3002.18 | 0.00520428 | 2.45303 | 9.02477 | 1.57409 | 0.00165227 | 2.0053e-05 | 1.39904e-06 | 5(Loss) | true |
