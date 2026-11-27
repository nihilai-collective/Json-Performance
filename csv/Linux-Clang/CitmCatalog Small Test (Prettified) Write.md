
----
### CitmCatalog Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10677.6 | 0.317763 | 796.055ms | 6938 | 1280 | 4962.97 | 619.673 | 0.315324 | 0.50574 | 1.76564 | 0.271404 | 0.000151003 | 1.85797e-05 | 2.92772e-06 | 1(Win) | true |
| Glaze | 3143.53 | 0.180442 | 949.38ms | 6960 | 4890 | 70984.9 | 2111.5 | 0.0916884 | 1.64912 | 4.23262 | 0.722702 | 0.000295848 | 2.51804e-05 | 4.81865e-06 | 2(Loss) | true |
