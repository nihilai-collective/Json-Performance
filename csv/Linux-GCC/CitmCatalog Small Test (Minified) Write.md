
----
### CitmCatalog Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8222.83 | 0.303644 | 757.396ms | 3223 | 30 | 38.6483 | 373.8 | 0.348993 | 0.71298 | 2.17716 | 0.283276 | 0.00031027 | 8.27386e-05 | 1.03423e-05 | 1(Win) | true |
| simdjson (reflection) | 7196.45 | 0.214874 | 763.02ms | 3223 | 2560 | 2156.21 | 427.113 | 0.0301718 | 0.783326 | 2.45734 | 0.313683 | 0.000311118 | 8.53242e-05 | 4.59345e-05 | 2(Loss) | true |
| Glaze | 3468.3 | 0.51792 | 808.969ms | 3223 | 320 | 6741.61 | 886.225 | 0.421385 | 1.55037 | 4.97084 | 0.759852 | 0.000316087 | 8.92026e-05 | 4.65405e-05 | 3(Loss) | true |
