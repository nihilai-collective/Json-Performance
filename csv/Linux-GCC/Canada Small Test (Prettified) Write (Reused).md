
----
### Canada Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5793.01 | 0.0579647 | 257.574ms | 14795 | 40 | 79.7276 | 2435.62 | 0.0290737 | 0.423107 | 1(Win) | true |
| Glaze | 3629.47 | 0.315082 | 407.514ms | 14795 | 1280 | 192044 | 3887.51 | 0.0464443 | 0.677418 | 2(Loss) | true |
| simdjson (reflection) | 474.27 | 0.111014 | 3007.69ms | 14795 | 2560 | 2.79239e+06 | 29750.2 | 0.358804 | 5.21551 | 3(Loss) | true |
