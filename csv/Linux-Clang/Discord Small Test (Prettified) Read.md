
----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2618.58 | 0.115869 | 247.242ms | 6701 | 40 | 319.846 | 2440.47 | 0.0351584 | 0.93536 | 1(Win) | true |
| Jsonifier (two-stage) | 2352.09 | 0.120764 | 274.821ms | 6701 | 80 | 861.265 | 2716.97 | 0.0681368 | 1.04226 | 2(Loss) | true |
| Glaze | 1848.64 | 0.153443 | 350.201ms | 6701 | 30 | 844.093 | 3456.9 | 0.0770809 | 1.328 | 3(Loss) | true |
| simdjson (ondemand) | 1087.46 | 0.111032 | 592.163ms | 6701 | 40 | 1702.96 | 5876.6 | 0.338615 | 2.26621 | 4(Loss) | true |
