
----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11612.1 | 0.118 | 765.336ms | 4390 | 4890 | 885.073 | 360.54 | 0.239291 | 0.485523 | 2.14055 | 0.346014 | 0.000229188 | 2.40368e-05 | 3.12106e-06 | 1(Win) | true |
| Glaze | 3992.43 | 0.308018 | 832.668ms | 4390 | 1280 | 13354.2 | 1048.64 | 0.220936 | 1.31711 | 5.37927 | 0.771071 | 0.000529969 | 4.28887e-05 | 1.74402e-05 | 2(Loss) | true |
