
----
### Discord Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14357.7 | 0.0833104 | 51.3574ms | 7376 | 160 | 26.6556 | 489.931 | 0.0932121 | 0.162314 | 1(Win) | true |
| Glaze | 3907.8 | 0.225304 | 186.865ms | 7376 | 30 | 493.444 | 1800.07 | 0 | 0.624259 | 2(Loss) | true |
| simdjson (reflection) | 523.9 | 0.137594 | 1393.63ms | 7376 | 1280 | 436874 | 13426.8 | 0.695829 | 4.71612 | 3(Loss) | true |
