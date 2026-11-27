
----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3812.29 | 0.0616134 | 127.405ms | 4669 | 80 | 41.4302 | 1167.99 | 0.0610396 | 0.635406 | 1(Win) | true |
| Jsonifier (two-stage) | 2692.41 | 0.12498 | 171.791ms | 4669 | 30 | 128.166 | 1653.8 | 0.0605034 | 0.905412 | 2(Loss) | true |
| Glaze | 1774.13 | 0.0823542 | 259.793ms | 4669 | 30 | 128.166 | 2509.8 | 0.119389 | 1.3808 | 3(Loss) | true |
| simdjson (reflection) | 1713.44 | 0.245992 | 269.856ms | 4669 | 2560 | 104614 | 2598.69 | 0.00652415 | 1.43051 | 4(Loss) | true |
| simdjson (ondemand) | 1241.33 | 0.341574 | 368.363ms | 4669 | 1280 | 192155 | 3587.03 | 0.0152218 | 1.98008 | 5(Loss) | true |
