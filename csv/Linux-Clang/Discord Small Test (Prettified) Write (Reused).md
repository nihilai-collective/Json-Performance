
----
### Discord Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12497 | 0.25057 | 796.485ms | 7376 | 4890 | 9727.5 | 562.881 | 0.475773 | 0.431846 | 1.46204 | 0.26166 | 0.000136379 | 2.21522e-05 | 1.82984e-06 | 1(Win) | true |
| Glaze | 3008.54 | 0.16683 | 977.344ms | 7376 | 4890 | 74402.7 | 2338.11 | 1.29212 | 1.71647 | 4.25231 | 0.667029 | 0.00125588 | 4.82136e-05 | 1.92134e-05 | 2(Loss) | true |
