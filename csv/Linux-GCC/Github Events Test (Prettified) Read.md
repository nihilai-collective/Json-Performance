
----
### Github Events Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1488.1 | 0.088077 | 4217.05ms | 65103 | 1280 | 1.72852e+06 | 41722.4 | 0.171193 | 1.66268 | 1(Win) | true |
| simdjson (ondemand) | 1322.94 | 0.166106 | 4783.17ms | 65103 | 320 | 1.94464e+06 | 46931 | 0.0408679 | 1.8704 | 2(Loss) | true |
