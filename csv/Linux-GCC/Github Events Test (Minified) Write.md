
----
### Github Events Test (Minified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14486.6 | 0.122887 | 396.919ms | 58581 | 30 | 673.775 | 3856.47 | 0.00605008 | 0.169733 | 1(Win) | true |
| simdjson (reflection) | 10988.2 | 0.0514725 | 514.83ms | 58581 | 40 | 273.948 | 5084.27 | 0.138691 | 0.22413 | 2(Loss) | true |
| Glaze | 6550.8 | 0.121263 | 851.918ms | 58581 | 4890 | 522986 | 8528.3 | 0.246642 | 0.376756 | 3(Loss) | true |
