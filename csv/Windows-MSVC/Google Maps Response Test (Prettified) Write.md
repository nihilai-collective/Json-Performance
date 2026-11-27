
----
### Google Maps Response Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 11143.5 | 0.139634 | 271.842ms | 31235 | 160 | 2229.17 | 2673.12 | 0.116768 | 0.220182 | 1(Win) | true |
| Glaze | 3904.07 | 0.102691 | 768.197ms | 31235 | 80 | 4911.39 | 7630 | 0.326584 | 0.631914 | 2(Loss) | true |
