
----
### Canada Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4484.18 | 0.0719232 | 1058.25ms | 14795 | 4890 | 25044.3 | 3146.53 | 0.059882 | 1.12614 | 2.9756 | 0.279892 | 0.000329299 | 1.37392e-05 | 2.9303e-06 | 1(Win) | true |
| Glaze | 3598.63 | 0.144737 | 1133.97ms | 14795 | 1280 | 41221.8 | 3920.83 | 0.198642 | 1.40313 | 4.44738 | 0.532815 | 0.000950226 | 1.23036e-05 | 1.37293e-06 | 2(Loss) | true |
