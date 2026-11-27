
----
### Google Maps Response Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20665.1 | 0.0666811 | 871.072ms | 31235 | 1280 | 1182.56 | 1441.47 | 0.270798 | 0.251646 | 0.739363 | 0.0796863 | 3.23655e-05 | 4.72727e-06 | 8.25396e-07 | 1(Win) | true |
| Glaze | 7441.38 | 0.193615 | 1139.11ms | 31235 | 640 | 38444.7 | 4003.03 | 0.221965 | 0.68561 | 3.62862 | 0.603938 | 0.000727049 | 1.47571e-05 | 4.70226e-06 | 2(Loss) | true |
| simdjson (reflection) | 544.102 | 0.218357 | 6282.89ms | 31235 | 1280 | 1.82922e+07 | 54747.1 | 0.00297113 | 9.25576 | 38.3009 | 7.06171 | 0.0180237 | 0.000143444 | 9.76469e-05 | 3(Loss) | true |
