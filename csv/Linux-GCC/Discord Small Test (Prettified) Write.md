
----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15901.3 | 0.0492648 | 47.3976ms | 7376 | 640 | 30.3971 | 442.373 | 0.158134 | 0.145994 | 1(Win) | true |
| Glaze | 3983.35 | 0.224555 | 177.373ms | 7376 | 80 | 1257.99 | 1765.92 | 0.183701 | 0.611909 | 2(Loss) | true |
| simdjson (reflection) | 538.689 | 0.117889 | 1298.82ms | 7376 | 2560 | 606671 | 13058.2 | 0.0179936 | 4.5862 | 3(Loss) | true |
