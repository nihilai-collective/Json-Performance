
----
### Apache Builds Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier DID NOT CONVERGE | 13075.8 | 0.457456 | 29.5629ms | 3643 | 80 | 118.187 | 265.7 | 2.82527 | 0.170543 | -(Win) | false |
| Glaze | 4376.4 | 0.111885 | 84.5795ms | 3682 | 320 | 257.885 | 802.356 | 0.276541 | 0.546828 | 2(Loss) | true |
| simdjson (reflection) | 557.481 | 0.429239 | 631.456ms | 3643 | 640 | 457969 | 6232.02 | 0.00318406 | 4.42164 | 3(Loss) | true |
