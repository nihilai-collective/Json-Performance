
----
### Canada Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1995 | 0.253059 | 949.914ms | 4630 | 320 | 10038.5 | 2213.28 | 0.00465958 | 2.58225 | 7.87991 | 0.433261 | 0.000223407 | 2.15983e-05 | 0 | 1(Win) | true |
| Glaze | 1008.13 | 0.0552736 | 1171.23ms | 4630 | 1280 | 7501.99 | 4379.91 | 0.14742 | 5.08154 | 9.27775 | 0.568036 | 0.000226613 | 9.06115e-05 | 4.28591e-05 | 2(Loss) | true |
