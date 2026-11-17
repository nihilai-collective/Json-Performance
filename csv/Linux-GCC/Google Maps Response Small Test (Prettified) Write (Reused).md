
----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 34071.7 | 0.137798 | 34.9495ms | 11521 | 80 | 15.7968 | 322.475 | 0.0698216 | 0.0668453 | 1(Win) | true |
| Glaze | 6335.19 | 0.0520672 | 177.334ms | 11521 | 80 | 65.2348 | 1734.33 | 0.0302803 | 0.384877 | 2(Loss) | true |
| simdjson (reflection) | 569.116 | 0.0591809 | 2010.67ms | 11521 | 30 | 3916.19 | 19305.9 | 0.556626 | 4.3446 | 3(Loss) | true |
