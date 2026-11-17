
----
### CitmCatalog Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16298 | 0.151502 | 42.9066ms | 6938 | 160 | 60.5277 | 405.975 | 0.339842 | 0.141552 | 1(Win) | true |
| Glaze | 4316.35 | 0.10435 | 158.167ms | 6960 | 40 | 102.999 | 1537.78 | 0.0113814 | 0.562859 | 2(Loss) | true |
| simdjson (reflection) | 538.394 | 0.168022 | 1245.75ms | 6938 | 2560 | 1.09154e+06 | 12289.5 | 0.13979 | 4.58857 | 3(Loss) | true |
