
----
### Instruments Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3808.14 | 0.142245 | 938.328ms | 7932 | 4890 | 39041 | 1986.41 | 0.268558 | 1.35443 | 5.95247 | 1.1736 | 0.000760606 | 1.80471e-05 | 3.99613e-06 | 1(Win) | true |
| Jsonifier (two-stage) | 3085.9 | 0.347507 | 982.8ms | 7932 | 640 | 46441.8 | 2451.32 | 0.0254392 | 1.67197 | 7.18848 | 1.17196 | 0.000653996 | 3.13209e-05 | 9.65236e-06 | 2(Loss) | true |
| Glaze | 2563.71 | 0.221481 | 1037.77ms | 7932 | 1280 | 54664.9 | 2950.62 | 0.0184514 | 1.99074 | 8.50277 | 1.56732 | 0.00148735 | 2.24565e-05 | 5.71262e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1131.94 | 0.0872197 | 1418.06ms | 7932 | 4890 | 166134 | 6682.82 | 0.0429479 | 4.46283 | 18.664 | 2.58258 | 0.00127606 | 3.60168e-05 | 1.60619e-05 | 4(Loss) | true |
