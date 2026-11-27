
----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7668.7 | 0.361109 | 64.3801ms | 4390 | 640 | 2487.38 | 545.938 | 0.114613 | 0.305919 | 1(Win) | true |
| Glaze | 3006.56 | 0.332519 | 143.112ms | 4390 | 80 | 1715.19 | 1392.5 | 0.535714 | 0.801469 | 2(Loss) | true |
